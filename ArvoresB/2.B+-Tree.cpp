#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define GRAU_MINIMO 3

/*
Procurar (e ou desenvolver), e testar,  a implementação de uma B+tree de ordem 3 (6 valores em cada nodo):
- inserção,
- exibição,
- busca de um valor,
- e remoção.
*/

/*
Codigos usados para implementar a ARVORE B+:
https://www.geeksforgeeks.org/c/implementation-of-b-plus-tree-in-c/
*/

typedef struct No {
    // Array de chaves
    int* chaves;
    // Grau minimo (define o intervalo para numero de chaves)
    int t;
    // Array de ponteiros para os filhos
    struct No** filhos;
    // Numero atual de chaves
    int n;
    // Para determinar se o no e folha ou nao
    bool folha;
    // Ponteiro para o proximo no folha
    struct No* proximo;
} No;

typedef struct ArvoreB {
    // Ponteiro para o no raiz
    No* raiz;
    // Grau minimo
    int t;
} ArvoreB;

// Funcao para criar um novo no da arvore B+
No* criarNo(int t, bool folha)
{
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->t = t;
    novoNo->folha = folha;
    novoNo->chaves = (int*)malloc((2 * t - 1) * sizeof(int));
    novoNo->filhos = (No**)malloc((2 * t) * sizeof(No*));
    novoNo->n = 0;
    novoNo->proximo = NULL;
    return novoNo;
}

// Funcao para criar uma nova arvore B+
ArvoreB* criarArvoreB(int t)
{
    ArvoreB* arvoreb = (ArvoreB*)malloc(sizeof(ArvoreB));
    arvoreb->t = t;
    arvoreb->raiz = criarNo(t, true);
    return arvoreb;
}

// Funcao para exibir a arvore B+ e imprimir suas chaves
void exibir(No* no)
{
    if (no == NULL)
        return;
    int i;
    for (i = 0; i < no->n; i++) {
        if (!no->folha) {
            exibir(no->filhos[i]);
        }
        printf("%d ", no->chaves[i]);
    }
    if (!no->folha) {
        exibir(no->filhos[i]);
    }
}

// Funcao para buscar uma chave na arvore B+
bool buscar(No* no, int chave)
{
    int i = 0;
    while (i < no->n && chave > no->chaves[i]) {
        i++;
    }
    if (i < no->n && chave == no->chaves[i]) {
        return true;
    }
    if (no->folha) {
        return false;
    }
    return buscar(no->filhos[i], chave);
}

// Funcao para dividir o filho de um no durante a insercao
void dividirFilho(No* pai, int i, No* filho)
{
    int t = filho->t;
    No* novoFilho = criarNo(t, filho->folha);
    novoFilho->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        novoFilho->chaves[j] = filho->chaves[j + t];
    }

    if (!filho->folha) {
        for (int j = 0; j < t; j++) {
            novoFilho->filhos[j] = filho->filhos[j + t];
        }
    }

    filho->n = t - 1;

    for (int j = pai->n; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = novoFilho;

    for (int j = pai->n - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[i] = filho->chaves[t - 1];
    pai->n += 1;
}

// Funcao para inserir em um no nao cheio
void inserirNaoCheio(No* no, int chave)
{
    int i = no->n - 1;

    if (no->folha) {
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->n += 1;
    }
    else {
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        i++;
        if (no->filhos[i]->n == 2 * no->t - 1) {
            dividirFilho(no, i, no->filhos[i]);
            if (no->chaves[i] < chave) {
                i++;
            }
        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}

// Funcao para inserir uma chave na arvore B+
void inserir(ArvoreB* arvoreb, int chave)
{
    No* raiz = arvoreb->raiz;
    if (raiz->n == 2 * arvoreb->t - 1) {
        No* novaRaiz = criarNo(arvoreb->t, false);
        novaRaiz->filhos[0] = raiz;
        dividirFilho(novaRaiz, 0, raiz);
        inserirNaoCheio(novaRaiz, chave);
        arvoreb->raiz = novaRaiz;
    }
    else {
        inserirNaoCheio(raiz, chave);
    }
}

// Funcao para encontrar o indice de uma chave em um no
int encontrarChave(No* no, int chave)
{
    int idx = 0;
    while (idx < no->n && chave > no->chaves[idx]) {
        idx++;
    }
    return idx;
}

// Funcao para mesclar o idx-esimo filho do no com o (idx + 1)-esimo
// filho do no
void mesclar(No* no, int idx)
{
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx + 1];

    // Puxando a chave do no atual e inserindo
    // na posicao (t-1) do filho
    filho->chaves[filho->n] = no->chaves[idx];

    // Se o filho nao e folha, mova os ponteiros dos filhos um
    // passo para frente
    if (!filho->folha) {
        filho->filhos[filho->n + 1] = irmao->filhos[0];
    }

    // Copiando as chaves do irmao para o filho
    for (int i = 0; i < irmao->n; ++i) {
        filho->chaves[i + filho->n + 1] = irmao->chaves[i];
    }

    // Se o filho nao e folha, copie os ponteiros dos filhos
    // tambem
    if (!filho->folha) {
        for (int i = 0; i <= irmao->n; ++i) {
            filho->filhos[i + filho->n + 1] = irmao->filhos[i];
        }
    }

    // Mova todas as chaves depois de idx no no atual um
    // passo antes, para cobrir o buraco criado ao mover
    // chaves[idx] para o filho
    for (int i = idx + 1; i < no->n; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }

    // Mova os ponteiros dos filhos depois de (idx + 1) no
    // no atual um passo antes
    for (int i = idx + 2; i <= no->n; ++i) {
        no->filhos[i - 1] = no->filhos[i];
    }

    // Atualize a contagem de chaves do filho e do no atual
    filho->n += irmao->n + 1;
    no->n--;

    // Libere a memoria ocupada pelo irmao
    free(irmao);
}

// Funcao para pegar emprestada uma chave do filho anterior e mover
// para o idx-esimo filho
void pegarEmprestadoAnterior(No* no, int idx)
{
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx - 1];

    // Mova todas as chaves no filho um passo para frente
    for (int i = filho->n - 1; i >= 0; --i) {
        filho->chaves[i + 1] = filho->chaves[i];
    }

    // Se o filho nao e folha, mova os ponteiros dos filhos um
    // passo para frente
    if (!filho->folha) {
        for (int i = filho->n; i >= 0; --i) {
            filho->filhos[i + 1] = filho->filhos[i];
        }
    }

    // Definindo a primeira chave do filho igual a do no
    // chaves[idx - 1]
    filho->chaves[0] = no->chaves[idx - 1];

    // Movendo o ultimo filho do irmao como o primeiro do filho
    if (!filho->folha) {
        filho->filhos[0] = irmao->filhos[irmao->n];
    }

    // Movendo a chave do irmao para o pai
    no->chaves[idx - 1] = irmao->chaves[irmao->n - 1];

    // Incrementando e decrementando a contagem de chaves
    // do filho e do irmao respectivamente
    filho->n += 1;
    irmao->n -= 1;
}

// Funcao para pegar emprestada uma chave do proximo filho e mover
// para o idx-esimo filho
void pegarEmprestadoProximo(No* no, int idx)
{
    No* filho = no->filhos[idx];
    No* irmao = no->filhos[idx + 1];

    // Definindo a chave (t - 1) do filho igual a do no
    // chaves[idx]
    filho->chaves[(filho->n)] = no->chaves[idx];

    // Se o filho nao e folha, mova os ponteiros dos filhos um
    // passo para frente
    if (!filho->folha) {
        filho->filhos[(filho->n) + 1]
            = irmao->filhos[0];
    }

    // Definindo a chave idx do no igual a primeira do
    // irmao
    no->chaves[idx] = irmao->chaves[0];

    // Movendo todas as chaves no irmao um passo para tras
    for (int i = 1; i < irmao->n; ++i) {
        irmao->chaves[i - 1] = irmao->chaves[i];
    }

    // Se o irmao nao e folha, mova os ponteiros dos filhos um
    // passo para tras
    if (!irmao->folha) {
        for (int i = 1; i <= irmao->n; ++i) {
            irmao->filhos[i - 1] = irmao->filhos[i];
        }
    }

    // Incrementando e decrementando a contagem de chaves
    // do filho e irmao respectivamente
    filho->n += 1;
    irmao->n -= 1;
}

// Funcao para preencher o no filho presente na posicao
// idx-esima no no atual
void preencher(No* no, int idx)
{
    if (idx != 0 && no->filhos[idx - 1]->n >= no->t) {
        pegarEmprestadoAnterior(no, idx);
    }
    else if (idx != no->n && no->filhos[idx + 1]->n >= no->t) {
        pegarEmprestadoProximo(no, idx);
    }
    else {
        if (idx != no->n) {
            mesclar(no, idx);
        }
        else {
            mesclar(no, idx - 1);
        }
    }
}

// Funcao para obter o predecessor de uma chave em um no nao
// folha
int obterPredecessor(No* no, int idx)
{
    No* atual = no->filhos[idx];
    while (!atual->folha) {
        atual = atual->filhos[atual->n];
    }
    return atual->chaves[atual->n - 1];
}

// Funcao para remover uma chave de um no folha
void removerDaFolha(No* no, int idx)
{
    for (int i = idx + 1; i < no->n; ++i) {
        no->chaves[i - 1] = no->chaves[i];
    }
    no->n--;
}

// Funcao auxiliar para remover recursivamente uma chave da arvore B+
// arvore
void removerChaveAuxiliar(No* no, int chave)
{
    int idx = encontrarChave(
        no, chave); // Encontra o indice da chave no no

    // Se a chave esta presente neste no
    if (idx < no->n && no->chaves[idx] == chave) {
        if (no->folha) {
            // Se o no e folha, simplesmente remova a chave
            removerDaFolha(no, idx);
        }
        else {
            // Se o no nao e folha, substitua a chave
            // pelo seu predecessor/sucessor
            int predecessor = obterPredecessor(no, idx);
            no->chaves[idx] = predecessor;
            // Remova recursivamente o predecessor
            removerChaveAuxiliar(no->filhos[idx], predecessor);
        }
    }
    else {
        // Se a chave nao esta presente neste no, desca
        // para o filho apropriado
        if (no->folha) {
            // Chave nao encontrada na arvore
            printf("Chave %d nao encontrada na arvore B+.\n",
                   chave);
            return;
        }

        bool ehUltimoFilho = (idx == no->n);

        // Se o filho onde a chave deve estar possui
        // menos de t chaves, preencha esse filho
        if (no->filhos[idx]->n < no->t) {
            preencher(no, idx);
        }

        // Se o ultimo filho foi mesclado, ele deve ter se
        // mesclado com o filho anterior

        // Sendo assim, precisamos remover a chave recursivamente
        // do filho anterior
        if (ehUltimoFilho && idx > no->n) {
            removerChaveAuxiliar(no->filhos[idx - 1], chave);
        }
        else {
            removerChaveAuxiliar(no->filhos[idx], chave);
        }
    }
}

// Funcao para deletar uma chave da arvore B+
void removerChave(ArvoreB* arvoreb, int chave)
{
    No* raiz = arvoreb->raiz;

    // Chama uma funcao auxiliar para remover a chave recursivamente
    removerChaveAuxiliar(raiz, chave);

    // Se a raiz nao tem mais chaves e tem um filho, torne seu
    // primeiro filho a nova raiz
    if (raiz->n == 0 && !raiz->folha) {
        arvoreb->raiz = raiz->filhos[0];
        free(raiz);
    }
}

int main()
{
    ArvoreB* arvoreb = criarArvoreB(GRAU_MINIMO);

    // Insere elementos na arvore B+
    inserir(arvoreb, 2);
    inserir(arvoreb, 4);
    inserir(arvoreb, 7);
    inserir(arvoreb, 10);
    inserir(arvoreb, 17);
    inserir(arvoreb, 21);
    inserir(arvoreb, 28);

    // Imprime a arvore B+
    printf("Arvore B+ apos a insercao: ");
    exibir(arvoreb->raiz);
    printf("\n");

    // Busca por uma chave
    int chave_para_buscar = 17;
    bool encontrado = buscar(arvoreb->raiz, chave_para_buscar);

    if (encontrado) {
        printf("Chave %d encontrada na arvore B+.\n", chave_para_buscar);
    }
    else {
        printf("Chave %d nao encontrada na arvore B+.\n", chave_para_buscar);
    }

    // Remove elemento da arvore B+
    removerChave(arvoreb, 17);

    // Imprime a arvore B+ apos a exclusao
    printf("Arvore B+ apos a exclusao: ");
    exibir(arvoreb->raiz);
    printf("\n");

    encontrado = buscar(arvoreb->raiz, chave_para_buscar);

    if (encontrado) {
        printf("Chave %d encontrada na arvore B+.\n", chave_para_buscar);
    }
    else {
        printf("Chave %d nao encontrada na arvore B+.\n", chave_para_buscar);
    }

    return 0;
}
