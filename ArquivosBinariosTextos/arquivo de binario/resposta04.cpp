#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct ponto{
	float x;
	float y;
};
typedef struct ponto PONTO;

PONTO maisdistante(char *arquivo){
	FILE * entrada = fopen(arquivo, "rb");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	float distancia = 0, calc;
	PONTO mais, aux;
	PONTO centro;
	centro.x = 2.61;
	centro.y = 1.19;
	while(fread(&aux, sizeof(PONTO), 1, entrada)){
		calc = sqrt(pow(centro.x-aux.x,2)+pow(centro.y-aux.y,2));
		if(calc > distancia){
			distancia = calc;
			mais = aux;
		}
	}
	fclose(entrada);
	return mais;
}

int main(){
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	PONTO distante = maisdistante(arquivo);
	printf("%.1f %.1f\n", distante.x, distante.y);
}
