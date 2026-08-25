#include <stdio.h>

float soma(int numero1, int numero2){
	return numero1 + numero2;
}

int main(){
	float numero1, numero2;
	printf("digite dois numeros: ");
	scanf("%f %f", &numero1, &numero2);
	printf("sua soma deu %.2f\n", soma(numero1, numero2));
	return 0;
}

