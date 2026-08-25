#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pais{
	char nome[50];
	int ouro, prata, bronze;
};
typedef struct pais PAIS;

void ordena(PAIS *pais, int n){
	int i, j;
	PAIS aux;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(pais[i].ouro < pais[j].ouro){
				aux = pais[i];
				pais[i] = pais[j];
				pais[j] = aux;
			}else{
				if(pais[i].ouro == pais[j].ouro && pais[i].prata < pais[j].prata){
					aux = pais[i];
					pais[i] = pais[j];
					pais[j] = aux;
				}else{
					if(pais[i].ouro == pais[j].ouro && pais[i].prata == pais[j].prata && pais[i].bronze < pais[j].bronze){
					aux = pais[i];
					pais[i] = pais[j];
					pais[j] = aux;
					}else{
						if(pais[i].ouro == pais[j].ouro && pais[i].prata == pais[j].prata && pais[i].bronze == pais[j].bronze && strcmp(pais[i].nome, pais[j].nome)>0){
							aux = pais[i];
							pais[i] = pais[j];
							pais[j] = aux;
						}
					}
				}
			}
		}
	}
	FILE *saida = fopen("saida_questao06.txt", "w");
	if(saida==NULL){
		printf("ERRO\n");
		exit(0);
	}
	for(i=0;i<n;i++){
		fprintf(saida, "%s %d %d %d\n", pais[i].nome, pais[i].ouro, pais[i].prata, pais[i].bronze);
	}
	fclose(saida);
}

void le_arquivo(char *arquivo){
	int i, n;
	FILE *entrada = fopen(arquivo, "r");
	if(entrada==NULL){
		printf("ERRO\n");
		exit(0);
	}
	fscanf(entrada, "%d\n", &n);
	PAIS pais[n];
	for(i=0;i<n;i++){
		fscanf(entrada, "%s %d %d %d\n", pais[i].nome, &pais[i].ouro, &pais[i].prata, &pais[i].bronze);
	}
	fclose(entrada);
	ordena(pais, n);
}

int main(){
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	le_arquivo(arquivo);
}
