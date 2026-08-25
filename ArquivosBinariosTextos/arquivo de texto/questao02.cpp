#include<stdio.h>
#include<stdlib.h>
#include<string.h>

float calcmedia(char *mat, char *arquivo){
	char matricula[50];
	float media = -1, n1, n2, n3;
	FILE *entrada = fopen(arquivo, "r");
	if(entrada == NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fscanf(entrada, "%s %f %f %f\n", matricula, &n1, &n2, &n3)==4){
		if(strcmp(matricula, mat)==0){
			media = (n1 + n2 + n3)/3;
			fclose(entrada);
			return media;
		}
	}
	fclose(entrada);
	return media;
}

int main(){
	char arquivo[50], mat[50];
	printf("digite o nome do arquivo\n");
	gets(arquivo);
	printf("digite a matricula do aluno\n");
	scanf("%s", mat);
	float media = calcmedia(mat, arquivo);
	printf("MEDIA: %.2f\n", media);
}
