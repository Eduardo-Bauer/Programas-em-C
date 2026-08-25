#include <stdio.h>

int maiorValor(int *lista, int tamanho){
    int i, maior = 0;
    for(i=0; i<tamanho; i++){
        if(lista[i] > maior){
            maior = lista[i];
        }
    }
    return maior;
}

void preencheLista(int *lista, int tamanho){
    int i;
    printf("digite seus %d valores:\n", tamanho);
    for(i=0; i<tamanho; i++){
        scanf("%d", &lista[i]);
    }
}

int main() {
    int tamanho, i;
    printf("digite o tamanho da lista: \n");
    scanf("%d", &tamanho);
    int lista[tamanho];
    
    preencheLista(lista, tamanho);
    printf("maior valor eh %d\n", maiorValor(lista, tamanho));
}