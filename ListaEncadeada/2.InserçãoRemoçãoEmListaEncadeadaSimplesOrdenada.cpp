#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista{
    char nome[20];
    struct lista *proximo;
}LISTA;

LISTA* inserirNome(LISTA *inicio, char *nome){
    LISTA*aux=inicio, *ant= NULL;
    LISTA*novo= (LISTA*)malloc(sizeof(LISTA));
    strcpy(novo->nome, nome);
    novo->proximo=NULL;
   
    if(inicio==NULL){
        inicio=novo;
        return inicio;
    }
   
    if(strcmp(novo->nome, inicio->nome) <=0){
        novo-> proximo=inicio;
        inicio=novo;
        return inicio;
    }
   
    while(aux!=NULL&&strcmp(aux->nome, novo->nome) <0){
        ant=aux;
        aux=aux->proximo;
    }

    ant->proximo = novo;
    novo->proximo = aux;
    return inicio;
}

LISTA*removerNome(LISTA*inicio, char*nome){
    LISTA*aux=inicio, *ant=NULL;  

    while (aux!=NULL) {
        if (strcmp(aux->nome, nome) ==0) {
            LISTA*temp=aux;

            if (ant==NULL) {
                inicio=aux->proximo;
                aux=inicio;

            } else {
                ant->proximo=aux->proximo;
                aux=ant->proximo;
            }
            free(temp);
           
        } else {
            ant=aux;
            aux=aux->proximo;
        }
    }
    return inicio;
}

LISTA*removerPosicao(LISTA*inicio, int posicao){
    LISTA*aux=inicio, *ant=NULL;
    int i=1;

    if(posicao==1){
        inicio=aux-> proximo;
        free(aux);
        return inicio;
    }

    while(aux!=NULL&&i<posicao){
        ant=aux;
        aux=aux->proximo;
        i++;
    }

    if(i==posicao&&aux!=NULL){
        ant->proximo=aux->proximo;
        free(aux);
    }
    return inicio;
}

void mostrarLista(LISTA*inicio){
    LISTA*aux=inicio;
    while(aux!=NULL){
        printf("%s\n", aux->nome);
        aux=aux->proximo;
    }
}

int main(){
    int opcao=1, posicao;
    char nome[20];
    LISTA*inicio=NULL;
   
    while(opcao!=0){
        printf("\n--------Bem Vindo--------\n");
        printf("1 - inserir nome\n");
        printf("2 - remover nome\n");
        printf("3 - remover posição\n");
        printf("4 - mostrar lista\n");
        printf("0 - sair\n");
        scanf("%d", &opcao);
       
        switch(opcao){
            case1:
                printf("Digite o nome que deseje inserir: ");
                scanf("%s", nome);
                inicio=inserirNome(inicio, nome);
                printf("Nome inserido com sucesso!\n");
                break;
           
            case2:
                printf("Digite o nome que deseje remover: ");
                scanf("%s", nome);
                inicio=removerNome(inicio, nome);
                printf("Nome removido com sucesso!\n");
                break;
               
            case3:
                printf("Digite a posicao que deseje remover: ");
                scanf("%d", &posicao);
                inicio=removerPosicao(inicio, posicao);
                printf("posição removida com sucesso!\n");
                break;
               
            case4:
                printf("\n--------Nomes na lista--------\n");
                mostrarLista(inicio);
                break;
               
            case0:
                printf("Encerrando o programa.....\n");
                break;
           
            default:
                printf("Opção não encontrada\n");
        }
       
    }
    return 0;
}