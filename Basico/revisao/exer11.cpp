#include <stdio.h>

void trocaValores(int *valor1, int *valor2){
    int troca;
    troca = *valor1;
    *valor1 = *valor2;
    *valor2 = troca;
}

int main() {
    int valor1, valor2;
    printf("digite dois valores para fazer a troca:");
    scanf("%d %d", &valor1, &valor2);
    
    trocaValores(&valor1, &valor2);
    printf("valor1: %d valor2: %d\n", valor1, valor2);
}