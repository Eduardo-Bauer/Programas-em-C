#include <stdio.h>

int main(){
	int a = 7, b = 4;
	
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	
	printf("a= %d b=%d\n", a, b);
}
