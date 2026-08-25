#include <stdio.h>
#include <stdlib.h>

struct data{
	int dia;
	int mes;
	int ano;
};
typedef struct data DATA;

struct livro{
	char titulo[50];
	char autor[50];
	DATA data;
};
typedef struct livro LIVRO;

void le_arquivo(char *arquivo, LIVRO *antigo, LIVRO *novo){
	LIVRO aux, troca;
	int cont=0;
	FILE *entrada = fopen(arquivo, "rb");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fread(&aux, sizeof(LIVRO), 1, entrada)){
		if(cont==0){
			*antigo = aux;
			*novo = aux;
			cont = 1;
		}else{
			if(aux.data.ano < antigo->data.ano){
				*antigo = aux;
			}else{
				if(aux.data.ano == antigo->data.ano && aux.data.mes < antigo->data.mes){
					*antigo = aux;
				}else{
					if(aux.data.ano == antigo->data.ano && aux.data.mes == antigo->data.mes && aux.data.dia < antigo->data.dia){
						*antigo = aux;
					}
				}
			}
		}
		if(aux.data.ano > novo->data.ano){
			*novo = aux;
		}else{
			if(aux.data.ano == novo->data.ano && aux.data.mes > novo->data.mes){
				*novo = aux;
			}else{
				if(aux.data.ano == novo->data.ano && aux.data.mes == novo->data.mes && aux.data.dia > novo->data.dia){
					*novo = aux;
				}
			}
		}
	}
	
	fclose(entrada);
}

int main(){
	LIVRO antigo, novo;
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	le_arquivo(arquivo, &antigo, &novo);
	printf("Livro mais antigo\n");
	printf("titulo: %s\nautor: %s\nedicao: %02d/%02d/%02d\n\n", antigo.titulo, antigo.autor, antigo.data.dia, antigo.data.mes, antigo.data.ano);
	printf("Livro mais novo\n");
	printf("titulo: %s\nautor: %s\nedicao: %02d/%02d/%02d\n", novo.titulo, novo.autor, novo.data.dia, novo.data.mes, novo.data.ano);
}
