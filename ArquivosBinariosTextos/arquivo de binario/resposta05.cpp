#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alunos{
	char nome[50];
	float n1, n2, n3;
};
typedef struct alunos ALUNOS;

void le_arquivo(char *arquivo){
	int cont=0, i, j;
	float auxmedia;
	ALUNOS aux;
	FILE *entrada = fopen(arquivo, "rb");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fread(&aux, sizeof(ALUNOS), 1, entrada)){
		cont++;
	}
	ALUNOS alunos[cont];
	float media[cont];
	rewind(entrada);
	for(i=0;i<cont;i++){
		fread(&alunos[i], sizeof(ALUNOS), 1, entrada);
		media[i] = (alunos[i].n1 + alunos[i].n2 + alunos[i].n3)/3;
	}
	fclose(entrada);
	for(i=0;i<cont-1;i++){
		for(j=i+1;j<cont;j++){
			if(media[i] < media[j]){
				aux = alunos[i];
				alunos[i] = alunos[j];
				alunos[j] = aux;
				auxmedia = media[i];
				media[i] = media[j];
				media[j] = auxmedia;
			}else{
				if(media[i] == media[j] && strcmp(alunos[i].nome, alunos[j].nome)>0){
					aux = alunos[i];
					alunos[i] = alunos[j];
					alunos[j] = aux;
					auxmedia = media[i];
					media[i] = media[j];
					media[j] = auxmedia;
				}
			}
		}
	}
	FILE *saida = fopen("saida_questao05.txt", "w");
	if(saida == NULL){
		printf("ERRO\n");
		exit(0);
	}
	for(i=0;i<cont;i++){
		fprintf(saida, "%s %.1f\n", alunos[i].nome, media[i]);
	}
	fclose(saida);
}

int main(){
	char arquivo[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	le_arquivo(arquivo);
}
