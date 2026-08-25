#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define NUM_ESPECIES 10

/*
1) Implemente um algoritmo de coloração (aproximada) de vértices.

A implementação deve informar qual o número cromático mínimo, e qual a cor de cada vértice.

Há sugestões (alguns links) nas páginas sobre Coloração.
*/

typedef struct{
    int id;
    int grau;
}Vertice;

int comparar_vertices(const void*a,const void*b){
    Vertice*v1=(Vertice*)a;
    Vertice*v2=(Vertice*)b;
    return v2->grau-v1->grau;
}

int main(){
    // Matriz de adjacência para representar os conflitos
    int adj[NUM_ESPECIES][NUM_ESPECIES]={0};

    adj[0][1]=1;adj[0][4]=1; // Espécie 1 conflita com 2 e 5
    adj[1][0]=1;adj[1][2]=1; // Espécie 2 conflita com 1 e 3
    adj[2][1]=1;adj[2][3]=1; // Espécie 3 conflita com 2 e 4
    adj[3][2]=1;adj[3][4]=1; // Espécie 4 conflita com 3 e 5
    adj[4][3]=1;adj[4][0]=1; // Espécie 5 conflita com 4 e 1


    Vertice vertices[NUM_ESPECIES];
    int cores[NUM_ESPECIES]={0}; // 0 indica que a espécie ainda não tem cercado
    int numero_cromatico=0;

    for(int i=0;i<NUM_ESPECIES;i++){
        vertices[i].id=i;
        vertices[i].grau=0;
        for(int j=0;j<NUM_ESPECIES;j++){
            if(adj[i][j]==1){
                vertices[i].grau++;
            }
        }
    }

    qsort(vertices,NUM_ESPECIES,sizeof(Vertice),comparar_vertices);

    for(int i=0;i<NUM_ESPECIES;i++){
        int v_atual=vertices[i].id;
       
        bool cor_usada_pelos_inimigos[NUM_ESPECIES+1]={false};

        // Verifica os inimigos da espécie atual
        for(int j=0;j<NUM_ESPECIES;j++){
            // Se 'j' é inimigo e já tem uma cor (cercado) atribuída
            if(adj[v_atual][j]==1&&cores[j]!=0){
                cor_usada_pelos_inimigos[cores[j]]=true;
            }
        }

        // Encontra a menor cor (número de cercado) disponível a partir de 1
        int cor_escolhida=1;
        while(cor_usada_pelos_inimigos[cor_escolhida]){
            cor_escolhida++;
        }

        cores[v_atual]=cor_escolhida;

        if(cor_escolhida>numero_cromatico){
            numero_cromatico=cor_escolhida;
        }
    }

    printf("Numero minimo de cercados (Numero Cromatico): %d\n\n",numero_cromatico);
    printf("Distribuicao das especies por cercado:\n");
   
    for(int i=0;i<NUM_ESPECIES;i++){
        printf("Especie %-2d -> Cercado %d\n",i+1,cores[i]);
    }

    return 0;
}