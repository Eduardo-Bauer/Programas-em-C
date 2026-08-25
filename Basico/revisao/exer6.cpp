#include <stdio.h>

int valoresNaoPrimos(int valor){
	if(valor == 1 || valor <= 0){
		return 1;
	}
	return 0;
}

int primo(int valor){
	int i;
	
	if(valoresNaoPrimos(valor)){
		return 0;
	}
	
	for(i = 3; i < valor; i++){
		if(valor % i == 0){
			return 0;
		}	
	}
	return 1;
}

int main(){
	int valor;
	printf("Digite um valor\n");
	scanf("%d", &valor);
	printf("%d", primo(valor));
}
