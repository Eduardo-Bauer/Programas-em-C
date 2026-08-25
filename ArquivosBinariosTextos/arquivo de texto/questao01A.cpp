#include <stdio.h>
#include <stdlib.h>

int main(){
	int aprovados = 0, reprovados = 0;
	float n1, n2, n3, media;
	char nome[50];
	FILE *entrada = fopen("exer01A.txt", "r");
	if(entrada==NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fscanf(entrada, "%s %f %f %f\n", nome, &n1, &n2, &n3)>0){
		media = (n1 + n2 + n3)/3;
		if(media>=6){
			aprovados++;
		}else{
			reprovados++;
		}
	}
	printf("APROVADOS: %d\n", aprovados);
	printf("REPROVADOS: %d\n", reprovados);
	fclose(entrada);
}
