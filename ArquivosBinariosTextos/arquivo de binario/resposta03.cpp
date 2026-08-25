#include<stdio.h>
#include<stdlib.h>

struct estado{
	char nome[31];
	int numveic;
	int numacid;
};
typedef struct estado ESTADO;

ESTADO estadomaior(char *arquivo){
	ESTADO maior;
	ESTADO aux;
	maior.numacid = 0;
	FILE *entrada = fopen(arquivo, "rb");
	while(fread(&aux, sizeof(ESTADO), 1, entrada)){
		if(aux.numacid > maior.numacid){
			maior = aux;
		}	
	}
	fclose(entrada);
	return maior;
}

int main(){
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	ESTADO maior = estadomaior(arquivo);
	printf("maior\n");
	printf("%s\n", maior.nome);
	printf("%d\n", maior.numveic);
	printf("%d\n", maior.numacid);
}
