#include <stdio.h>
#include <stdlib.h>

int le_arquivo(char *arquivo){
	int aux, cont = 0;
	FILE *entrada = fopen(arquivo, "rb");
	if(entrada==NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fread(&aux, sizeof(int), 1, entrada)){
		printf("%d\n", aux);
		cont++;
	}
	fclose(entrada);
	return cont;
}

void insere_valor(char *arquivo, int n, int cont){
	int vetor[cont+1], i, j, aux;
	FILE *entrada = fopen(arquivo, "rb+");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	for(i=0;i<cont;i++){
		fread(&vetor[i], sizeof(int), 1, entrada);
	}
	rewind(entrada);
	vetor[i] = n;
	for(i=0;i<cont;i++){
		for(j=i+1;j<cont+1;j++){
			if(vetor[i] > vetor[j]){
				aux = vetor[i];
				vetor[i] = vetor[j];
				vetor[j] = aux;
			}
		}
		fwrite(&vetor[i], sizeof(int), 1, entrada);
	}
	fwrite(&vetor[i], sizeof(int), 1, entrada);
	fclose(entrada);
}

int main(){
	int n;
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	int contador = le_arquivo(arquivo);
	printf("------------------------\n");
	printf("digite o numero para adicionar\n");
	scanf("%d", &n);
	printf("-----------------------\n");
	insere_valor(arquivo, n, contador);
	contador = le_arquivo(arquivo);
}

