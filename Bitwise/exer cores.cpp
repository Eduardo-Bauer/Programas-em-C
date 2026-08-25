#include <stdio.h>
//483D8B (72,61,139)

void busca_rgb(unsigned int cor, int *r, int *g, int *b){
	*b = cor & 0xff;
	*g = (cor >> 8) & 0xff;
	*r = (cor >> 16) & 0xff;
	
}

unsigned int busca_cor(int r, int g, int b){
	unsigned int cor = b;
	cor = (g << 8) | cor;
	cor = (r << 16) | cor;
	return cor;
}

int main(){
	unsigned int cor = 0x483D8B;
	int r, g, b;
	
	busca_rgb(cor, &r, &g, &b);
	printf("R: %d G: %d B: %d\n", r, g, b);
	printf("%x\n", busca_cor(72, 61, 139));
}
