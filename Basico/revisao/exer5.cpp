#include <stdio.h>

int fatorial(int numero){
	int i, valor = 1;
	for(i = 1; i <= numero; i++){
		valor *= i;
	}
	return valor;
}

int main(){
	int valor;
	printf("Digite o valor para achar o fatorial\n");
	scanf("%d", &valor);
	printf("fatorial eh %d \n", fatorial(valor));
}
