#include <stdio.h>
#include <stdlib.h>

void le_arquivo(char *arquivo, int *vet){
	int numero;
	FILE *entrada = fopen(arquivo, "rb");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fread(&numero, sizeof(int), 1, entrada)){
		vet[numero-1]++;
	}
	fclose(entrada);
}

int main(){
	int vet[5] = {0}, i, j;
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	le_arquivo(arquivo, vet);
	FILE *saida = fopen("saida_questao02.txt", "w");
	for(i=0;i<5;i++){
		fprintf(saida, "%d ", i+1);
		for(j=0;j<vet[i];j++){
			fprintf(saida, "*");
		}
		fprintf(saida, "\n");
	}
	fclose(saida);
}
