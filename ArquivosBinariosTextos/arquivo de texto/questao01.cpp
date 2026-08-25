#include <stdio.h>
#include <stdlib.h>

int main(){
	int aprovados = 0, reprovados = 0;
	float n1, n2, n3, media;
	char nome[50];
	FILE *entrada = fopen("exer01.txt", "r");
	if(entrada==NULL){
		printf("ERRO\n");
		exit(0);
	}
	while(fgets(nome, 50, entrada)>0){
		fscanf(entrada, "%f %f %f\n", &n1, &n2, &n3);
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
