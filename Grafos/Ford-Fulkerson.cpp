#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<string.h>

// Define o número de vértices do grafo
#define VERTICES 6

/*
Fazer uma implementação do algoritmo de Ford-Fulkerson, que a partir de uma rede fornecida encontra seu fluxo máximo.
*/

bool busca_em_largura(int grafo_residual[VERTICES][VERTICES],int fonte,int sumidouro,int pai[]){
    bool visitado[VERTICES];
    memset(visitado,0,sizeof(visitado));

    int fila[VERTICES];
    int inicio=0,fim=0;

    fila[fim++]=fonte;
    visitado[fonte]=true;
    pai[fonte]=-1;

    while(inicio<fim){
        int u=fila[inicio++];

        for(int v=0;v<VERTICES;v++){
            // Verifica se o vizinho 'v' não foi visitado e se há capacidade residual
            if(visitado[v]==false&&grafo_residual[u][v]>0){
                if(v==sumidouro){
                    pai[v]=u;
                    return true;
                }
                fila[fim++]=v;
                pai[v]=u;
                visitado[v]=true;
            }
        }
    }
    // Retorna falso se não alcançamos o sumidouro a partir da fonte
    return false;
}

int ford_fulkerson(int grafo[VERTICES][VERTICES],int fonte,int sumidouro){
    int u,v;

    // grafo_residual[u][v] indicará a capacidade residual da aresta de u para v.
    int grafo_residual[VERTICES][VERTICES];
    for(u=0;u<VERTICES;u++){
        for(v=0;v<VERTICES;v++){
            grafo_residual[u][v]=grafo[u][v];
        }
    }

    int pai[VERTICES];

    int fluxo_maximo=0;

    while(busca_em_largura(grafo_residual,fonte,sumidouro,pai)){
        // Encontra o fluxo máximo que pode passar pelo caminho encontrado.
        // É a capacidade residual mínima ("gargalo") entre as arestas do caminho.
        int fluxo_caminho=INT_MAX;
        for(v=sumidouro;v!=fonte;v=pai[v]){
            u=pai[v];
            if(grafo_residual[u][v]<fluxo_caminho){
                fluxo_caminho=grafo_residual[u][v];
            }
        }

        // Atualiza as capacidades residuais das arestas ao longo do caminho
        for(v=sumidouro;v!=fonte;v=pai[v]){
            u=pai[v];
            grafo_residual[u][v]-=fluxo_caminho; // Subtrai o fluxo da aresta direta
            grafo_residual[v][u]+=fluxo_caminho; // Adiciona o fluxo na aresta reversa
        }

        fluxo_maximo+=fluxo_caminho;
    }

    return fluxo_maximo;
}

int main(){
    int grafo[VERTICES][VERTICES]={
        {0,16,13,0,0,0},
        {0,0,10,12,0,0},
        {0,4,0,0,14,0},
        {0,0,9,0,0,20},
        {0,0,0,7,0,4},
        {0,0,0,0,0,0}
    };

    int fonte=0;
    int sumidouro=5;

    printf("O fluxo máximo possível na rede é: %d\n",ford_fulkerson(grafo,fonte,sumidouro));

    return 0;
}