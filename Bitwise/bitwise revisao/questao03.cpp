#include <stdio.h>

char rodaparaesquerda(char n, char nbits){
	char m;
	char menor = (n>>(7-nbits));
	m = (n<<3) + menor;
	return m;
}

int main(){
	char n = 77;
	char nbits = 3;
	char m = rodaparaesquerda(n, nbits);
	printf("%d\n", m);
}
