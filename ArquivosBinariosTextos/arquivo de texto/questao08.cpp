#include <stdio.h>
#include <stdlib.h>

int contador(char *arquivo){
	int cont=0, aux;
	FILE *entrada = fopen(arquivo, "r");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fscanf(entrada, "%d\n", &aux)==1){
		cont++;
	}
	fclose(entrada);
	return cont;
}

void le_arquivo(int *vet, char *arquivo, int tamanho){
	int i;
	FILE *entrada = fopen(arquivo, "r");
	if(entrada==NULL){
		printf("ERRO\n");
		exit(0);
	}
	for(i=0;i<tamanho;i++){
		fscanf(entrada, "%d\n", &vet[i]);
	}
	fclose(entrada);
}

int main(){
	char arquivo1[50], arquivo2[50];
	int aux;
	printf("digite o primeiro arquivo\n");
	gets(arquivo1);
	printf("digite o segundo arquivo\n");
	gets(arquivo2);
	int tamanho1 = contador(arquivo1);
	int tamanho2 = contador(arquivo2);
	int vet1[tamanho1];
	int vet2[tamanho2];
	int vet3[tamanho1+tamanho2];
	le_arquivo(vet1, arquivo1, tamanho1);
	le_arquivo(vet2, arquivo2, tamanho2);
	int i, j;
	for(i=0;i<tamanho1;i++){
		vet3[i] = vet1[i];
	}
	for(j=0;j<tamanho2;j++){
		vet3[i+j] = vet2[j];
	}
	for(i=0;i<tamanho1+tamanho2-1;i++){
		for(j=i+1;j<tamanho1+tamanho2;j++){
			if(vet3[i] > vet3[j]){
				aux = vet3[i];
				vet3[i] = vet3[j];
				vet3[j] = aux;
			}
		}
	}
	FILE *saida = fopen("saida_questao08.txt", "w");
	if(saida == NULL){
		printf("ERRO\n");
		exit(0);
	}
	for(i=0;i<tamanho1 + tamanho2;i++){
		fprintf(saida, "%d\n", vet3[i]);
	}
	fclose(saida);
}
