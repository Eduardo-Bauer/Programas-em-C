#include<stdio.h>

int main(){
	int n;
	
	printf("digite o valor\n");
	scanf("%d", &n);
	
	if(n & 1){
		printf("o valor %d eh impar\n", n);
	}else{
		printf("o valor %d eh par\n", n);
	}
}
