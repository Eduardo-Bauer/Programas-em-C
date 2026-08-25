#include <stdio.h>

int main(){
	unsigned short int compacto;
	char c1, c2, desc1, desc2;
	printf("digite o primeiro e segundo caracter\n");
	scanf("%c %c", &c1, &c2);
	compacto = c1;
	compacto = (compacto<<8) | c2;
	printf("COMPACTADO: %u\n", compacto);
	desc2 = (char)compacto & 0xff;
	desc1 = (char)(compacto>>8);
	printf("DESCOMPACTADO: %c %c", desc1, desc2);
	
}
