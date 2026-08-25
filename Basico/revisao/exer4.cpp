#include <stdio.h>
#include <math.h>

float calculaAreaQuadrado(float ladoQuadrado){
	return pow(ladoQuadrado, 2);
}

float calculaAreaTriangulo(float semiperimetro, float ladoA, float ladoB, float ladoC){
	return sqrt(semiperimetro * (semiperimetro - ladoA) * (semiperimetro - ladoB) * (semiperimetro - ladoC));
}

float calculaAreaCirculo(float raio){
	float pi = 3.14;
	return (pi * pow(raio, 2));
}

void imprimeArea(float area){
	printf("A area eh %.2f\n", area);
}

int main(){
	float semiperimetro, ladoA, ladoB, ladoC, raio, ladoQuadrado;
	printf("Digite o valor do lado do quadrado: ");
	scanf("%f", &ladoQuadrado);
	imprimeArea(calculaAreaQuadrado(ladoQuadrado));
	
	printf("Digite o valor para o triangulo: semiperimetro, ladoA, ladoB e lacoC: ");
	scanf("%f %f %f %f", &semiperimetro, &ladoA, &ladoB, &ladoC);
	imprimeArea(calculaAreaTriangulo(semiperimetro, ladoA, ladoB, ladoC));
	
	printf("Digite o valor do raio do circulo: ");
	scanf("%f", &raio);
	imprimeArea(calculaAreaCirculo(raio));
}
