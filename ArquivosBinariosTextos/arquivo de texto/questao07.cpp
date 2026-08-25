#include <stdio.h>
#include <stdlib.h>

int main(){
	int codigo, quant, i;
	float media, valor;
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	FILE *entrada = fopen(arquivo, "r");
	FILE *saida = fopen("media.txt", "w");
	if(entrada == NULL || saida == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fscanf(entrada, "%d ", &codigo)>0){
		fscanf(entrada, "%d ", &quant);
		media = 0;
		for(i=0;i<quant;i++){
			fscanf(entrada, "%f ", &valor);
			media += valor;
		}
		media /= quant;
		fscanf(entrada, "\n");
		fprintf(saida, "% 5d %d %.1f\n", codigo, quant, media);
	}
}
