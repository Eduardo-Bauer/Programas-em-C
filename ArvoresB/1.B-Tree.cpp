#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMANHO 4

/*
Códigos usados para implementar a B-TREE:
https://www.geeksforgeeks.org/dsa/delete-operation-in-b-tree/
https://www.geeksforgeeks.org/c/implementation-of-b-tree-in-c/
*/

typedef struct No {
    int n_chaves;
    int chaves[TAMANHO - 1];
    struct No *filhos[TAMANHO];
    bool eh_folha;
} TNo;

TNo* CriarNo(){
    TNo *no = (TNo*)malloc(sizeof(TNo));
    no->n_chaves = 0;
    no->eh_folha = true;

    for(int i = 0; i < TAMANHO; i++){
        no->filhos[i] = NULL;
    }

    return no;
}

// percorre em ordem
void PercorrerArvore(TNo *raiz){
    if(raiz != NULL){
        int i;
        for(i = 0 ; i < raiz->n_chaves; i++){
            if (!raiz->eh_folha) PercorrerArvore(raiz->filhos[i]);
            printf("%d ", raiz->chaves[i]);
        }
        if (!raiz->eh_folha) PercorrerArvore(raiz->filhos[i]);
    }
}

// divide o nó em dois e reordena eles
void SplitFilhos(TNo *parente, int index){
    TNo *filho = parente->filhos[index];
    TNo *novo = CriarNo();
    novo->eh_folha = filho->eh_folha;

    novo->n_chaves = TAMANHO/2 - 1;

    for(int i = 0; i < TAMANHO/2 - 1; i++){
        novo->chaves[i] = filho->chaves[i + TAMANHO/2];
    }

    if(!filho->eh_folha){
        for(int i = 0; i < TAMANHO/2; i++){
            novo->filhos[i] = filho->filhos[i + TAMANHO/2];
        }
    }

    filho->n_chaves = TAMANHO/2 - 1;

    for(int i = parente->n_chaves; i >= index + 1; i--){
        parente->filhos[i + 1] = parente->filhos[i];
    }

    parente->filhos[index + 1] = novo;

    for(int i = parente->n_chaves - 1; i >= index; i--){
        parente->chaves[i + 1] = parente->chaves[i];
    }

    parente->chaves[index] = filho->chaves[TAMANHO/2 - 1];
    parente->n_chaves++;
}

// insere valor no nó em seu lugar em ordem crescente
void InserirNoNaoCheio(TNo *no, int valor){
    int i = no->n_chaves - 1;

    if(no->eh_folha){
        while(i >= 0 && no->chaves[i] > valor){
            no->chaves[i+1] = no->chaves[i];
            i--;
        }

        no->chaves[i + 1] = valor;
        no->n_chaves++;
    } else {
        while(i >= 0 && no->chaves[i] > valor){
            i--;
        }
       
        if(no->filhos[i + 1]->n_chaves == TAMANHO - 1){
            SplitFilhos(no, i + 1);

            if(no->chaves[i + 1] < valor){
                i++;
            }
        }
        InserirNoNaoCheio(no->filhos[i + 1], valor);
    }
}

// chama as outras inserções e cria a raiz
void InserirNo(TNo **raiz, int valor){
    TNo *aux = *raiz;

    if(aux == NULL){
        *raiz = CriarNo();
        (*raiz)->n_chaves = 1;
        (*raiz)->chaves[0] = valor;
        return;
    }

    if(aux->n_chaves == TAMANHO - 1){
        TNo *novo = CriarNo();
        novo->eh_folha = false;
        novo->filhos[0] = aux;
        SplitFilhos(novo, 0);
       
        int i = (novo->chaves[0] < valor) ? 1 : 0;
        InserirNoNaoCheio(novo->filhos[i], valor);
       
        *raiz = novo;
    } else {
        InserirNoNaoCheio(*raiz, valor);
    }
}

// auxiliar para encontrar a primeira chave maior ou igual a valor
int EncontrarChave(TNo *no, int valor) {
    int index = 0;
    while (index < no->n_chaves && no->chaves[index] < valor) {
        ++index;
    }
    return index;
}

// rebalanceia o filho no->filhos[idx] se ele tiver menos do que grau - 1 chaves
void Preencher(TNo *no, int idx) {
    int grau = TAMANHO / 2;

    // caso A: emprestar do irmão esquerdo
    if (idx != 0 && no->filhos[idx - 1]->n_chaves >= grau) {
        TNo *filho = no->filhos[idx];
        TNo *irmao = no->filhos[idx - 1];

        for (int i = filho->n_chaves - 1; i >= 0; --i) {
            filho->chaves[i + 1] = filho->chaves[i];
        }

        if (!filho->eh_folha) {
            for (int i = filho->n_chaves; i >= 0; --i) {
                filho->filhos[i + 1] = filho->filhos[i];
            }
        }

        filho->chaves[0] = no->chaves[idx - 1];

        if (!filho->eh_folha) {
            filho->filhos[0] = irmao->filhos[irmao->n_chaves];
        }

        no->chaves[idx - 1] = irmao->chaves[irmao->n_chaves - 1];
        filho->n_chaves++;
        irmao->n_chaves--;
    }
    // caso B: emprestar do irmão direito
    else if (idx != no->n_chaves && no->filhos[idx + 1]->n_chaves >= grau) {
        TNo *filho = no->filhos[idx];
        TNo *irmao = no->filhos[idx + 1];

        filho->chaves[filho->n_chaves] = no->chaves[idx];

        if (!filho->eh_folha) {
            filho->filhos[filho->n_chaves + 1] = irmao->filhos[0];
        }

        no->chaves[idx] = irmao->chaves[0];

        for (int i = 1; i < irmao->n_chaves; ++i) {
            irmao->chaves[i - 1] = irmao->chaves[i];
        }

        if (!irmao->eh_folha) {
            for (int i = 1; i <= irmao->n_chaves; ++i) {
                irmao->filhos[i - 1] = irmao->filhos[i];
            }
        }

        filho->n_chaves++;
        irmao->n_chaves--;
    }
    // caso C: fundir com um irmão
    else {
        int i = (idx != no->n_chaves) ? idx : idx - 1;
        TNo *filho = no->filhos[i];
        TNo *irmao = no->filhos[i + 1];

        filho->chaves[grau - 1] = no->chaves[i];

        for (int j = 0; j < irmao->n_chaves; ++j) {
            filho->chaves[j + grau] = irmao->chaves[j];
        }

        if (!filho->eh_folha) {
            for (int j = 0; j <= irmao->n_chaves; ++j) {
                filho->filhos[j + grau] = irmao->filhos[j];
            }
        }

        for (int j = i + 1; j < no->n_chaves; ++j) {
            no->chaves[j - 1] = no->chaves[j];
        }

        for (int j = i + 2; j <= no->n_chaves; ++j) {
            no->filhos[j - 1] = no->filhos[j];
        }

        filho->n_chaves += irmao->n_chaves + 1;
        no->n_chaves--;
        free(irmao);
    }
}

// remove de um nó específico
void RemoverDeNo(TNo *no, int valor) {
    int index = EncontrarChave(no, valor);
    int grau = TAMANHO / 2;

    if (index < no->n_chaves && no->chaves[index] == valor) {
        if (no->eh_folha) {
            // deleção de nó folha
            for (int i = index + 1; i < no->n_chaves; ++i) {
                no->chaves[i - 1] = no->chaves[i];
            }

            no->n_chaves--;

        } else {
            // Deleção de nó interno
            if (no->filhos[index]->n_chaves >= grau) {
                TNo *filho = no->filhos[index];

                while (!filho->eh_folha) {
                    filho = filho->filhos[filho->n_chaves];
                }

                int proximo = filho->chaves[filho->n_chaves - 1];
                no->chaves[index] = proximo;

                RemoverDeNo(no->filhos[index], proximo);
            }

            else if (no->filhos[index + 1]->n_chaves >= grau) {
                // Usar sucessor
                TNo *filho = no->filhos[index + 1];

                while (!filho->eh_folha) {
                    filho = filho->filhos[0];
                }

                int proximo = filho->chaves[0];
                no->chaves[index] = proximo;

                RemoverDeNo(no->filhos[index + 1], proximo);
            }
            else {
                // fundir e deletar
                Preencher(no, index);
                RemoverDeNo(no, valor);
            }
        }
    } else {
        // Chave não está neste nó
        if (no->eh_folha) {
            printf("\nA chave %d não está na árvore.\n", valor);
            return;
        }

        bool flag = (index == no->n_chaves);

        if (no->filhos[index]->n_chaves < grau) {
            Preencher(no, index);
        }

        if (flag && index > no->n_chaves) {
            RemoverDeNo(no->filhos[index - 1], valor);
        } else {
            RemoverDeNo(no->filhos[index], valor);
        }
    }
}

// função principal de remoção a ser chamada na raiz
void RemoverDaArvore(TNo **raiz, int k) {

    RemoverDeNo(*raiz, k);

    if ((*raiz)->n_chaves == 0) {
        TNo *aux = *raiz;
        if ((*raiz)->eh_folha) {
            *raiz = NULL;
        } else {
            *raiz = (*raiz)->filhos[0];
        }
        free(aux);
    }
}

int main(){
    int valores[10] = {1, 5, 8, 3, 0, 2, 4, 6, 9, 21};
    TNo *arvore = NULL;

    printf("Inserindo valores...\n");
    for(int i = 0; i < 10; i++){
        InserirNo(&arvore, valores[i]);
    }

    printf("Árvore atual: ");
    PercorrerArvore(arvore);
    printf("\n");

    printf("Removendo o valor 5...\n");
    RemoverDaArvore(&arvore, 5);

    printf("Árvore após remoção: ");
    PercorrerArvore(arvore);
    printf("\n");
   
    return 0;
}
