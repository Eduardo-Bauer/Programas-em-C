#include <stdio.h>
void imprimeASCII(unsigned char *arquivo){
	int i, j;
	for(i=0;i<8;i++){
		for(j=7;j>=0;j--){
			if((arquivo[i]>>j)&1){
				printf("#");
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(){
	unsigned char arquivo[8] = {0xe7, 0xe7, 0xe7, 0x7e, 0x3c, 0x3c, 0x7e, 0xff};
	imprimeASCII(arquivo);
}
