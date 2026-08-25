#include<stdio.h>
#include<stdlib.h>

/*
Uma palíndrome é um texto (ou palavra) que pode ser lido da esquerda para a direita
ou da direita para a esquerda, produzindo o mesmo resultado (ou o mesmo texto). 
Por exemplo: "arara", "amor e roma", "ele", "1234554321". 

Considere que um texto está armazenado em uma lista duplamente encadeada, 
na qual cada nodo contém um caractere. 
Implemente uma função (em C, C#, C++, Java, Python) que verifique se o texto armazenado 
é uma palíndrome ou não, 
retornando 0 se o texto não for palíndrome e 1 se for palíndrome.
*/

typedef struct nodulo{
    char caractere;
    struct nodulo*proximo, *anterior;
}NODULO;

typedef struct header{
    int quant;
    struct nodulo*inicio, *fim;
}HEADER;

void escrever(NODULO*inicio){
    NODULO*aux=inicio;

    while(aux!=NULL){
        printf("%c\n", aux->caractere);
        aux=aux->proximo;
    }
    printf("\n");
}

void inserirChar(NODULO**inicio, HEADER**header, char caractere){
    NODULO*aux=*inicio;
    NODULO*novo= (NODULO*)malloc(sizeof(NODULO));
    novo->anterior=NULL;
    novo->caractere=caractere;
    novo->proximo=NULL;

    if(aux==NULL){
        *inicio=novo;
       
        (*header)->inicio=novo;
        (*header)->fim=novo;
        (*header)->quant=1;
    }else{
        while(aux->proximo!=NULL){
            aux=aux->proximo;
        }
        aux->proximo=novo;
        novo->anterior=aux;

        (*header)->fim=novo;
        (*header)->quant++;
    }
}

int  conferirPalindromo(NODULO*inicio, HEADER*header){
    NODULO*aux=inicio;
    NODULO*fim=header->fim;
    int quant=header->quant;

    while((aux!=NULL&&fim!=NULL) &&quant>1){
        if(aux->caractere!=fim->caractere){
            return 0;
        }
        quant-=2;
        aux=aux->proximo;
        fim=fim->anterior;
    }
    return 1;
}

int main(){
    NODULO*inicio=NULL;

    HEADER*header= (HEADER*)malloc(sizeof(HEADER));
    header->inicio=NULL;
    header->fim=NULL;
    header->quant=NULL;

    inserirChar(&inicio, &header, 'a');
    inserirChar(&inicio, &header, 'r');
    inserirChar(&inicio, &header, 'a');
    inserirChar(&inicio, &header, 'r');
    inserirChar(&inicio, &header, 'a');

    escrever(inicio);

    printf("%d\n", conferirPalindromo(inicio, header));
    return 0;
}