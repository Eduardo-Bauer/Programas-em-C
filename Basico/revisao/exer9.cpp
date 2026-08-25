#include <stdio.h>

float CelsiusParaFahrenheit(int c){
	return (1.8 * c) + 32;
}

int main(){
	int celsius;
	printf("digite os Graus Celsius\n");
	scanf("%d", &celsius);
	printf("Fahrenheit %.2f\n", CelsiusParaFahrenheit(celsius));
}
