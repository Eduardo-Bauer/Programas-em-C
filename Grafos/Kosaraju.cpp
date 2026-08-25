/*
Grafo igual ao do exercício do slide 731:
*/

#include<stdio.h>

#define V 10 // Número de vértices (A até J)

/*
Implementar o algoritmo de Kosaraju para identificação de subgrafos fortemente conexos de um grafo. 

A entrada é um grafo, e a saída é a enumeração de cada um dos seus componentes fortemente conexos.
*/

void reverter_matriz(int mat[V][V],int matriz_reversa[V][V]){
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            if(mat[i][j]){
                matriz_reversa[j][i]=1;
            }
        }
    }
}

void pesquisar_dfs(int matriz[V][V],int*visitados,int*vertice_ordem,int vertice,int*ponteiro){
    visitados[vertice]=1;

    for(int i=0;i<V;i++){
        if(matriz[vertice][i]&&visitados[i]==0){
            pesquisar_dfs(matriz,visitados,vertice_ordem,i,ponteiro);
        }
    }

    vertice_ordem[(*ponteiro)++]=vertice;
}

void descobrir_componentes_fortemente_conexos(int matriz_reversa[V][V],int*vertice_ordem,int*visitados){
    int contador=0;
   
    for(int i=V-1;i>=0;i--){
        if(visitados[vertice_ordem[i]]==0){
            int ponteiro=0;
            int fortemente_conexos[V]={0};
            pesquisar_dfs(matriz_reversa,visitados,fortemente_conexos,vertice_ordem[i],&ponteiro);

            printf("%d. ",contador++);

            for(int i=ponteiro-1;i>=0;i--){
                printf("%c",fortemente_conexos[i]+65);

                if(i!=0){
                    printf("-> ");
                }
            }

            printf("\n");
        }
    }
}

int main(){
    int ponteiro=0;

    int vertice_ordem[V]={0};

    int visitados[V]={0};

    int matriz_reversa[V][V]={0};

    int matriz[V][V]={
        // A  B  C  D  E  F  G  H  I  J
        {  0,0,0,1,0,0,0,0,0,0  }, // A (A -> D)
        {  0,0,1,0,1,0,0,0,0,0  }, // B (B -> C, B -> E)
        {  0,0,0,0,0,0,1,0,0,0  }, // C (C -> G)
        {  0,0,0,0,0,0,0,1,0,0  }, // D (D -> H)
        {  0,0,0,0,0,0,0,0,1,0  }, // E (E -> I)
        {  0,0,1,0,1,0,1,0,0,0  }, // F (F -> C, F -> E, F -> G)
        {  0,0,1,0,0,0,0,0,0,0  }, // G (G -> C)
        {  0,0,0,0,0,0,0,0,1,0  }, // H (H -> I)
        {  0,0,0,1,0,0,0,0,0,1  }, // I (I -> D, I -> J)
        {  0,0,0,0,0,1,1,0,0,0  }  // J (J -> F, J -> G)
    };

    reverter_matriz(matriz,matriz_reversa);

    for(int i=0;i<V;i++){
        if(visitados[i]==0){
            pesquisar_dfs(matriz,visitados,vertice_ordem,i,&ponteiro);
        }

    }

    printf("componentes fortemente conexos:\n");

    int visitados_conexos[V]={0};

    descobrir_componentes_fortemente_conexos(matriz_reversa,vertice_ordem,visitados_conexos);
}