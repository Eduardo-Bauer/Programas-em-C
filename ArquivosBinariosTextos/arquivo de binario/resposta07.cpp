#include <stdio.h>
#include <stdlib.h>

struct data{
	int dia;
	int mes;
	int ano;
};
typedef struct data DATA;

struct funci{
	int codigo;
	char nome[50];
	DATA nasci;
	float valor_hora;
};
typedef struct funci FUNCI;

void le_arquivo(char *arquivo){
	FUNCI aux;
	FILE *entrada = fopen(arquivo, "rb");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fread(&aux, sizeof(FUNCI), 1, entrada)){
		printf("%d   %s   %02d/%02d/%02d   %.2f\n\n", aux.codigo, aux.nome, aux.nasci.dia, aux.nasci.mes, aux.nasci.ano, aux.valor_hora);
	}
	fclose(entrada);
}

void modifica(char *arquivo, int codigo, float valor){
	FUNCI aux;
	FILE *entrada = fopen(arquivo, "rb+");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fread(&aux, sizeof(FUNCI), 1, entrada)){
		if(aux.codigo == codigo){
			aux.valor_hora = valor;
			fseek(entrada, -sizeof(FUNCI), SEEK_CUR);
			fwrite(&aux, sizeof(FUNCI), 1, entrada);
			fclose(entrada);
			break;
		}
	}
}

int main(){
	int codigo;
	float valor;
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	le_arquivo(arquivo);
	printf("---------------------------------------\n");
	printf("digite o codigo do funcionario para alterar seu valor\n");
	scanf("%d", &codigo);
	printf("digite o valor novo do funcionario\n");
	scanf("%f", &valor);
	modifica(arquivo, codigo, valor);
	le_arquivo(arquivo);
}
