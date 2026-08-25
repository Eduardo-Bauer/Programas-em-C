/*
gráfico de 8 nódulos da página 476.
*/

#include<stdio.h>
 
#define N 8

/*
Implementar um método de ordenação topológica.

A entrada é um grafo, e a saída uma (ou mais) sequência(s) de ordenação topológica possível.
*/

void ordem_topologica(int*peso, int*visitado, int mat[N][N]){
    for(int i=0; i<N; i++){
        peso[i] =0;

        for(int j=0; j<N; j++){
            peso[i] +=mat[i][j];
        }

        if(peso[i] ==0&&visitado[i] ==0){
            visitado[i] =1;

            for(int j=0; j<N; j++){
                mat[j][i] =0;
            }

            ordem_topologica(peso, visitado, mat);

            printf("%c - ", i+65);
           
            break;
        }
    }
}

int main(){
    int peso[N] = {0};

    int visitado[N] = {0};

    int mat[N][N] = {
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ordem_topologica(peso, visitado, mat);
}
