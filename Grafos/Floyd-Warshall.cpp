#include<stdio.h>

#define V 8
#define INF 999999

/*
Faça uma implementação do algoritmo de Floyd-Warshall para encontrar o caminho mínimo de cada vértice 
como vértice inicial até todos os outros vértices:

- deve escrever a distância mínima cada vértice até cada um dos outros vértices

- e, para cada distância escrita, deve escrever o caminho percorrido (enumerar os vértices que compuseram aquele caminho mínimo
*/


// funçao recursiva para reconstruir e imprimir os vertices intermediarios do caminho
void caminho(int path[V][V],int i,int j){
    if(path[i][j]!=i){
        caminho(path,i,path[i][j]);

        printf("%d -> ",path[i][j]);
    }
}

// funçao retirada do geeksforgeeks, mas com alteraçao para gerar a matriz do caminho
void floyd(int dist[V][V],int path[V][V]){
    for(int k=0;k<V;k++){
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(dist[i][k]!=INF&&dist[k][j]!=INF){
                    if(dist[i][j]>dist[i][k]+dist[k][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];

                        path[i][j]=path[k][j];
                    }
                }
            }
        }
    }
}


int main(){
    // a diagonal principal deve ser 0
    int dist[V][V]={
        {  0,INF,INF,   8,   9,INF,INF,INF},
        {INF,   0,   5,   7,INF,INF,INF,INF},
        {INF,INF,   0,INF,   6,   6,INF,INF},
        {INF,INF,INF,   0,INF,INF,INF,   2},
        {INF,INF,   4,INF,   0,INF,INF,   2},
        {INF,   8,INF,INF,INF,   0,INF,   8},
        {INF,INF,   3,INF,INF,INF,   0,INF},
        {INF,INF,INF,INF,INF,INF,INF,   0}
    };
                     
    int path[V][V]; // matriz do caminho
   
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(dist[i][j]!=INF&&i!=j){
                path[i][j]=i; // i e j sao vizinhos
            }else{
                path[i][j]=-1; // sem caminho inicial
            }
        }
    }

    floyd(dist,path);
   
    printf("Pesos (Distancias Minimas):\n");
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(dist[i][j]==INF){
                printf("INF ");
            }else{
                printf("%3d",dist[i][j]);
            }
        }
        printf("\n");
    }
   
    printf("\nMatriz de Predecessores (Path):\n");
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            printf("%2d",path[i][j]);
        }
        printf("\n");
    }
   
    printf("\nCaminhos Bonitos (Origem -> ... -> Destino):\n");
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(dist[i][j]!=INF&&i!=j){
                printf("%d -> ",i);

                caminho(path,i,j);

                printf("%d\n",j);
            }
        }
    }
    return 0;
}