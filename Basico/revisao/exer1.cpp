#include <stdio.h>

int parOuImpar(int numero){
	return numero % 2;
}

void mensagem(int resultado){
	if(resultado){
		printf("eh um impar");
	}else{
		printf("eh um par");
	}
}

int main(){
	int numero;
	printf("Digite um numero: ");
	scanf("%d", &numero);
	mensagem(parOuImpar(numero));
	return 0;
}
