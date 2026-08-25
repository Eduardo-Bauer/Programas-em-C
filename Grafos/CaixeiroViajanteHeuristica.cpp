#include <stdio.h>
#define INF 999

int visinho_proxino(int inicio, int mat[10][10], int *visitados, int *caminho){
    int total_visitados = 0;
    int valor_inicial = inicio;
    int proximo;
    int total = 0;

    while(total_visitados < 10){
        int menor = INF;
        visitados[inicio] = 1;
        total_visitados++;

        for(int i = 0; i < 10; i++){
            if(mat[inicio][i] < menor && visitados[i] == 0){
                menor = mat[inicio][i];
                caminho[inicio] = i;
                proximo = i;
            }
        }

        if(menor == INF){
            caminho[inicio] = valor_inicial;
        }

        total += mat[inicio][caminho[inicio]];

        printf("teste %d -> %d\n", inicio, caminho[inicio]);

        inicio = proximo;
    }

    return total;
}

int main(){
    int visitados[10] = {0};
    int caminhos[10] = {0};
    int mat[10][10] = {
        {00, 18, 61, 74, 20, 99, 31, 18, 28, 92},
        {15, 00, 31, 78, 54, 87, 35, 85, 32, 68},
        {38, 82, 00, 49, 82, 70, 62, 10, 46, 77},
        {92, 36, 66, 00, 81, 95, 61, 42, 52, 64},
        {44, 73, 32, 14, 00, 70, 49, 49, 25, 97},
        {63, 72, 63, 14, 83, 00, 14, 48, 35, 51},
        {18, 37, 11, 17, 42, 14, 00, 33, 13, 63},
        {86, 75, 25, 41, 49, 51, 35, 00, 47, 68},
        {56, 60, 16, 71, 78, 10, 38, 41, 00, 36},
        {25, 17, 15, 27, 31, 17, 27, 73, 53, 00},
    };

    printf("total do caminho: %d\n", visinho_proxino(0, mat, visitados, caminhos));
}
