#include<stdio.h>

int compactahora(int hora, int minuto, int segundo){
	int compacta = hora;
	compacta = (compacta<<8) | minuto;
	compacta = (compacta<<8) | segundo;
	return compacta;
	
}

void descompacta(int codificado, int *hora, int *minuto, int *segundo){
	*segundo = codificado & 0xff;
	*minuto = (codificado>>8) & 0xff;
	*hora = (codificado>>16) & 0xff;
}

int main(){
	int hora, minuto, segundo;
	hora = 14;
	minuto = 32;
	segundo = 25;
	int codifica = compactahora(hora, minuto, segundo);
	printf("%x %d\n", codifica);
	descompacta(codifica, &hora, &minuto, &segundo);
	printf("%02d/%02d/%02d\n", hora, minuto, segundo);
}
