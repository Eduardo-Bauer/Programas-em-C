#include <stdio.h>

int tamanhoVetor(int *vetor){
	int i = 0;
	while(*(vetor++)){
		i++;
	}
	return i;
}

int somaVetor(int *vetor){
	int i, soma = 0;
	int tamanho = tamanhoVetor(vetor);
	
	for(i = 0; i < tamanho; i++){
		soma += vetor[i];
	}
	return soma;
}

int main(){
	int vetor[] = {1, 2, 3, 4, 5};
	printf("%d\n", somaVetor(vetor));
}
