#include <stdio.h>

void troca(int *n1, int *n2){
	*n1 = *n1 ^ *n2;
	*n2 = *n1 ^ *n2;
	*n1 = *n1 ^ *n2;
}

int main(){
	int n1, n2;
	printf("digite os valores para trocar\n");
	scanf("%d %d", &n1, &n2);
	troca(&n1, &n2);
	printf("n1 = %d\nn2 = %d\n", n1, n2);
}
