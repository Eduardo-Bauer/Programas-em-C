#include <stdio.h>
#include <ctype.h>

int numeroVogais(char *str){
    int i, contador = 0;
    char letra;
    for(i=0; str[i] != '\0'; i++){
        letra = toupper(str[i]);
        if(letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U'){
            contador++;
        }
    }
    return contador;
}

int main() {
    char texto[50];
    int vogais;
    printf("Digite seu texto: \n");
    fgets(texto, sizeof(texto), stdin);
    
    vogais = numeroVogais(texto);
    printf("%d vogais\n", vogais);
}