#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct compra{
	char nome[50];
	float preco;
};
typedef struct compra COMPRA;

float le_frutas(char *arquivo){
	int n, i, j, quant, aux;
	char fruta[50];
	float valor = 0;
	FILE *entrada = fopen(arquivo, "r");
	if(entrada==NULL){
		printf("ERRO\n");
		exit(0);
	}
	fscanf(entrada, "%d\n", &n);
	COMPRA compra[n];
	for(i=0;i<n;i++){
		fscanf(entrada, "%s %f\n", compra[i].nome, &compra[i].preco);
	}
	fscanf(entrada, "%d\n", &aux);
	for(i=0;i<aux;i++){
		fscanf(entrada, "%s %d\n", fruta, &quant);
		for(j=0;j<n;j++){
			if(strcmp(fruta, compra[j].nome)==0){
				valor += compra[j].preco * quant;
				break;
			}
		}	
	}
	fclose(entrada);
	return valor;
}

int main(){
	FILE *saida = fopen("saida_questao04.txt", "w");
	if(saida==NULL){
		printf("ERRO\n");
		exit(0);
	}
	float valor = 0;
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	valor = le_frutas(arquivo);
	fprintf(saida, "R$ %.2f\n", valor);
	fclose(saida);
	printf("CONFIRA O DOCUMENTO GERADO\n");
}
