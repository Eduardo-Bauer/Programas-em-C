#include <stdio.h>
int verificaValores(float valor1, float valor2){
	if(valor1 == 0 || valor2 == 0){
		return 0;
	}
	return 1;
}

float divisao(float valor1, float valor2){
	return valor1 / valor2;
}

int main(){
	float valor1, valor2;
	printf("digite dois valores: ");
	scanf("%f %f", &valor1, &valor2);
	
	if(verificaValores(valor1, valor2)){
		printf("%.2f\n", divisao(valor1, valor2));
	}else{
		printf("Valor de 0 detectado\n");		
	}

}
