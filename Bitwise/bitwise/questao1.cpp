#include <stdio.h>

void impar(unsigned int n){
	if(n & 1 == 1){
		printf("eh primo\n");
	}else{
		printf("nao eh primo\n");
	}
}

int main(){
	unsigned int n;
	printf("digite seu valor\n");
	scanf("%u", &n);
	impar(n);
}
