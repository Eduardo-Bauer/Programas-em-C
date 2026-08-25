#include <stdio.h>

int main(){
	unsigned int n, bit[32] = {0};
	int i=31;
	printf("digite seu numero\n");
	scanf("%u", &n);
	while(n>0){
		bit[i] = n & 1;
		i--;
		n = n>>1;
	}
	for(i=0;i<32;i++){
		printf("%u", bit[i]);
	}
}
