#include<stdio.h>

unsigned char minusculo(unsigned char c){
	if(c>='A' && c<='Z'){
		c = c | ('a'-'A');
	}
	return c;
}

unsigned char maiusculo(unsigned char c){
	if(c>='a' && c<='z'){
		c = c & 0xdf;//223
	}
	return c;
}

int main(){
	printf("%c\n", minusculo('A'));
	printf("%c\n", minusculo('M'));
	printf("%c\n", minusculo('Z'));
	printf("%c\n", maiusculo('a'));
	printf("%c\n", maiusculo('m'));
	printf("%c\n", maiusculo('z'));
}
