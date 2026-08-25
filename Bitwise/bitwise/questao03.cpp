#include <stdio.h>

void maiuscula_minuscula(char caracter){
	if(caracter >= 'a' && caracter <= 'z'){
		caracter = caracter ^ ('a'-'A');
	}else{
		caracter = caracter | ('a' - 'A');
	}
	printf("%c\n", caracter);
}

int main(){
	char caracter;
	printf("digite seu caracter\n");
	scanf("%c", &caracter);
	maiuscula_minuscula(caracter);
}
