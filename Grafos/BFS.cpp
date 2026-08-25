/*
Faça uma função para verificar se um grafo é conexo (isso é, de cada vértice pode-se chegar a todos os outros por algum caminho),
efetuando uma busca (BFS) e verificando se algum vértice deixou de ser visitado.

Teste com grafo dirigido e grafo não dirigido
*/

#include<stdio.h>

#define N 5

int bfs(int inicio, int matriz[N][N], int nivel[N]){
    int fila[N], PA=1, TD=0, soma =1;
   
    fila[0] = inicio;
    nivel[inicio] =0;
   
    while(PA!=TD){
        int vertice=fila[TD++];
       
        for(int i=0; i<=N; i++){
            if(matriz[vertice][i] ==1&&nivel[i] ==-1){
                fila[PA++] = i;
                nivel[i] =nivel[vertice] +1;
                soma++;
            }
        }
    }

    return soma / N;
}

int main(){
    int matriz[N][N] = {0};
    int nivel[N];
   
    for(int i=0; i<N; i++){
        nivel[i] =-1;  
    }

    /* grafo conexo dirigido
    matriz[0][1] = 1;
    matriz[1][2] = 1;
    matriz[1][4] = 1;
    matriz[4][3] = 1;
    */

    /* grafo nao conexo dirigido
    matriz[0][1] = 1;
    matriz[1][2] = 1;
    matriz[3][4] = 1;
    */

    // grafo conexo nao dirigido
    matriz[0][1] =1;
    matriz[1][0] =1;
    matriz[1][2] =1;
    matriz[2][1] =1;
    matriz[1][4] =1;
    matriz[4][1] =1;
    matriz[4][3] =1;
    matriz[3][4] =1;

    /* grafo nao conexo nao dirigido
    matriz[0][1] =1;
    matriz[1][0] =1;
    matriz[1][2] =1;
    matriz[2][1] =1;
    matriz[3][4] =1;
    matriz[4][3] =1;
    */

    for(int i=0; i<N; i++){
        if(bfs(i, matriz, nivel)){
            printf("eh conexo\n");
            break;

        }else{
            if(i == N-1){
                printf("nao eh conexo\n");
            }
        }
    }
}