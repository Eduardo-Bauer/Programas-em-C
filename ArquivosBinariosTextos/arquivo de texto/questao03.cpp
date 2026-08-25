#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct funci{
	char cpf[15];
	char nome[50];
	float salario;
	char funcao[50];
};typedef struct funci FUNCI;

void ordena(FUNCI *funcionario, int n){
	int i, j;
	FUNCI aux;
	FILE *saida = fopen("saida_questao03.txt", "w");
	if(saida==NULL){
		printf("ERRO\n");
		exit(0);
	}
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(strcmp(funcionario[i].nome, funcionario[j].nome)>0){
				aux = funcionario[i];
				funcionario[i] = funcionario[j];
				funcionario[j] = aux;
			}
		}
	}
	for(i=0;i<n;i++){
		fprintf(saida, "%s\n%s%.2f\n%s\n\n", funcionario[i].cpf, funcionario[i].nome, funcionario[i].salario, funcionario[i].funcao);
	}
	fclose(saida);
}

void learquivo(char *arquivo){
	int n, i;
	FILE *entrada = fopen(arquivo, "r");
	if(entrada==NULL){
		printf("ERRO\n");
		exit(0);
	}
	fscanf(entrada, "%d\n", &n);
	FUNCI funcionario[n];
	for(i=0;i<n;i++){
		fscanf(entrada, "%s\n", funcionario[i].cpf);
		fgets(funcionario[i].nome, 50, entrada);
		fscanf(entrada, "%f\n", &funcionario[i].salario);
		fscanf(entrada, "%s\n", funcionario[i].funcao);
	}
	fclose(entrada);
	ordena(funcionario, n);
}
int main(){
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	learquivo(arquivo);
	printf("documento gerado\n");
}
