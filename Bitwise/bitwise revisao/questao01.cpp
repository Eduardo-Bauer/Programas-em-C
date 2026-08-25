#include <stdio.h>

int crossover(int n, int m){
	int cross = (n>>16);
	cross = cross<<16;
	cross = cross + (m&0xffff);
	return cross;
}

int main(){
	int n = 305419896;
	int m = 1737075661;
	int cross = crossover(n, m);
	printf("%d\n", cross);
}
