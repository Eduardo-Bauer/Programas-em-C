#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
Implementação de AVL

Implementar uma AVL (desenvolver seu código ou utilizar um código existente), 
com as seguintes operações: inserção, remoção e percurso (testar alguns, que ajudem a entender a estrutura da árvore).

Os valores armazenados podem ser números (ou textos se você preferir...).

OBS: se utilizou um código existente, colocar a fonte
*/

typedef struct nodulo{
    int numero;
    int altura;
    int fb;
    struct nodulo *esq;
    struct nodulo *dir;
} NODULO;

// teste para ver a ordem que a arvore se encontra, se crescente, ta certo
void PercorrerArvore(NODULO *nodulo){
    if(nodulo != NULL){
        PercorrerArvore(nodulo->esq);
        printf("%d -> ", nodulo->numero);
        PercorrerArvore(nodulo->dir);
    }
}

NODULO* CriarNodulo(int numero){
    NODULO *novo = (NODULO *) malloc(sizeof(NODULO));
    if(novo == NULL){
        exit(1);
    }

    novo->numero = numero;
    novo->altura = 0;
    novo->fb = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

void InserirNodulo(NODULO **arvore, int valor){
    NODULO *no = CriarNodulo(valor);
    NODULO *aux = *arvore;
    NODULO *anterior = aux;
   
    if(*arvore == NULL){
        *arvore = no;
        return;
    }

    while(aux != NULL){
        anterior = aux;

        if(no->numero < aux->numero){
            aux = aux->esq;

        }else{
            aux = aux->dir;
        }
    }

    if(no->numero < anterior->numero){
        anterior->esq = no;

    }else{
        anterior->dir = no;
    }
}

void ExcluirNodulo(NODULO **arvore, int numero){
    if (*arvore == NULL) {
            return;
    }

    if (numero < (*arvore)->numero) {
        ExcluirNodulo(&(*arvore)->esq, numero);
    }

    else if (numero > (*arvore)->numero) {
        ExcluirNodulo(&(*arvore)->dir, numero);
    }

    else {
        NODULO *aux = *arvore;

        if ((*arvore)->esq == NULL) {
            *arvore = (*arvore)->dir;
            free(aux);
        }

        else if ((*arvore)->dir == NULL) {
            *arvore = (*arvore)->esq;
            free(aux);
        }

        else {
            // buscar o maior elemento da sub-árvore esquerda
            NODULO *maiorEsq = (*arvore)->esq;

            while (maiorEsq->dir != NULL) {
                maiorEsq = maiorEsq->dir;
            }
           
            (*arvore)->numero = maiorEsq->numero;
           
            ExcluirNodulo(&(*arvore)->esq, maiorEsq->numero);
        }
    }
}

// retorna a altura do balanceamento
int CalcularAlturaNodulo(NODULO **nodulo){
    int alt_nodulo = 0;
    int alt_direita = -1;
    int alt_esquerda = -1;

    if(*nodulo == NULL){
        return -1;
    }

    alt_esquerda = CalcularAlturaNodulo(&(*nodulo)->esq);
    alt_direita = CalcularAlturaNodulo(&(*nodulo)->dir);

    alt_nodulo = 1 + fmax (alt_esquerda, alt_direita);

    (*nodulo)->altura = alt_nodulo;

    return alt_nodulo;
}

int PegarAlturaNodulo(NODULO *nodulo){
    if(nodulo == NULL){
        return -1;
    }

    return nodulo->altura;
}

// retorna NULL se balanceado ou vazio, se não ta balanceado,
// retorna um ponteiro com o nodulo não balanceado
// fb = altura esquerda - altura direita
NODULO** CalcularBalanceamentoArvore(NODULO **nodulo){
int fb = 0;

    if(*nodulo == NULL){
        return NULL;
    }

    NODULO **desbalanceadoEsq = CalcularBalanceamentoArvore(&(*nodulo)->esq);
    if(desbalanceadoEsq != NULL){
        return desbalanceadoEsq;
    }

    NODULO **desbalanceadoDir = CalcularBalanceamentoArvore(&(*nodulo)->dir);
    if(desbalanceadoDir != NULL){
        return desbalanceadoDir;
    }

    fb = PegarAlturaNodulo((*nodulo)->esq) - PegarAlturaNodulo((*nodulo)->dir);
    (*nodulo)->fb = fb;

    if(abs(fb) >= 2){
        return nodulo;
    }

    return NULL;
}

void RotacionarEsquerdaArvore(NODULO **nodulo) {
    NODULO *desbalanceado = *nodulo;
    NODULO *novaRaiz = desbalanceado->dir;

    desbalanceado->dir = novaRaiz->esq;

    novaRaiz->esq = desbalanceado;

    *nodulo = novaRaiz;
}

void RotacionarDireitaArvore(NODULO **nodulo) {
    NODULO *desbalanceado = *nodulo;      
    NODULO *novaRaiz = desbalanceado->esq;

    desbalanceado->esq = novaRaiz->dir;

    novaRaiz->dir = desbalanceado;

    *nodulo = novaRaiz;
}

void RotacionarDireitaEsquerdaArvore(NODULO **nodulo) {
    RotacionarDireitaArvore(&(*nodulo)->dir);
    RotacionarEsquerdaArvore(nodulo);
}

void RotacionarEsquerdaDireitaArvore(NODULO **nodulo) {
    RotacionarEsquerdaArvore(&(*nodulo)->esq);
    RotacionarDireitaArvore(nodulo);
}

void BalancearArvore(NODULO **nodulo){
    if((*nodulo)->fb < 0){
        // desbalanceada para direita e fazer rotacao para a esquerda
        if((*nodulo)->dir->fb < 0){
            RotacionarEsquerdaArvore(nodulo);
            return;
        }

        // fazer a rotação dupla
        RotacionarDireitaEsquerdaArvore(nodulo);
        return;
    }

    // desbalanceada para esquerda e fazer rotacao para a direita
    if((*nodulo)->esq->fb > 0){
        RotacionarDireitaArvore(nodulo);
        return;
    }

    //fazer a rotação dupla esquerda direita
    RotacionarEsquerdaDireitaArvore(nodulo);
}

int main(){
    NODULO *arvore = NULL;
    NODULO **balanceamento = NULL;
    int insersoes[10] = {10, 20, 15, 30, 50, 53, 3, 5, 7, 9};
    int removidos[3] = {20, 3, 50};

    for(int i = 0; i < 10; i++){
        InserirNodulo(&arvore, insersoes[i]);

        PercorrerArvore(arvore);
        printf("\n");

        CalcularAlturaNodulo(&arvore);
        balanceamento = CalcularBalanceamentoArvore(&arvore);

        if(balanceamento != NULL){
            printf("balanceando\n");

            BalancearArvore(balanceamento);
        };
    }

    printf("\nEXCLUINDO COISAS\n");

    for(int i = 0; i < 3; i++){
        ExcluirNodulo(&arvore, removidos[i]);

        PercorrerArvore(arvore);
        printf("\n");

        CalcularAlturaNodulo(&arvore);
        balanceamento = CalcularBalanceamentoArvore(&arvore);

        if(balanceamento != NULL){
            printf("balanceando\n");

            BalancearArvore(balanceamento);
        };
    }

    PercorrerArvore(arvore);
}

// referências:
// https://www.youtube.com/watch?v=YkF76cOgtMQ
// https://www.youtube.com/watch?v=2tXA9-0z4iI 