#include<stdio.h>
#include<stdlib.h>

float le_arquivo(char *arquivo){
	int cont = 0;
	float numero;
	float media = 0;
	FILE *entrada = fopen(arquivo, "rb");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fread(&numero, sizeof(float), 1, entrada)){
		media += numero;
		cont++;
	}
	media /= cont;
	fclose(entrada);
	return media;
}

int main(){
	float media;
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	media = le_arquivo(arquivo);
	printf("%.2f\n", media);
}
