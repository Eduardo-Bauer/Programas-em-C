#include <stdio.h>

void adicionaPrimo(int local, int valor, int *vetor){
    vetor[local] = valor;
}

int verificaValor(int valor){
    if(valor <= 1){
        return 1;
    }
    return 0;
}

int primos(int inicio, int final, int *vetor){
    int i, j, naoEPrimo;
    int local = 0;
    for(i = inicio; i < final; i++){
        naoEPrimo = 0;

        if (verificaValor(i)){
            naoEPrimo = 1;
            continue;
        }
        
        for(j = 2; j < i; j++){
            if(i % j == 0){
                naoEPrimo = 1;
                break;
            }
        }
        if (naoEPrimo == 0){
            adicionaPrimo(local, i, vetor);
            local++;
        }
    }
    return local;
}

void verificaMaior(int *inicio, int *final){
    int troca;
    if(*inicio > *final){
        troca = *inicio;
        *inicio = *final;
        *final = troca;
    }
}

void imprimePrimos(int qtdPrimos, int *vetor){
    int i;
    printf("Primos Encontrados:\n");
    for(i=0; i<qtdPrimos; i++){
        printf("%d ", vetor[i]);
    }
}

int main() {
    int inicio = 100, final = 200, qtdPrimos;
    verificaMaior(&inicio, &final);
    int vetor[final - inicio];
    qtdPrimos = primos(inicio, final, vetor);
    imprimePrimos(qtdPrimos, vetor);
    
}