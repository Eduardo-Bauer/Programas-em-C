#include <stdio.h>
#include <stdlib.h>

/*
Faça uma implementação do algoritmo de Kruskal para obtenção de uma AGM. 
O programa deve ter como entrada um grafo valorado, e exibir como saída a lista das arestas que formam a AGM.
*/

// Estrutura para representar uma aresta do grafo
struct Aresta {
    int origem, destino, peso;
};

// Estrutura para representar um grafo conectado, não direcionado e valorado
struct Grafo {
    int V, E; // V = número de vértices, E = número de arestas
    struct Aresta* aresta;
};

// Estrutura para os subconjuntos do Union-Find
struct subconjunto {
    int pai;
    int rank;
};

// Função para criar um grafo com V vértices e E arestas
struct Grafo* criarGrafo(int V, int E) {
    struct Grafo* grafo = (struct Grafo*) malloc(sizeof(struct Grafo));
    grafo->V = V;
    grafo->E = E;
    grafo->aresta = (struct Aresta*) malloc(E * sizeof(struct Aresta));
    return grafo;
}

// Função utilitária para encontrar o conjunto de um elemento i
// Utiliza a técnica de Compressão de Caminho
int buscar(struct subconjunto subconjuntos[], int i) {
    if (subconjuntos[i].pai != i)
        subconjuntos[i].pai = buscar(subconjuntos, subconjuntos[i].pai);
    return subconjuntos[i].pai;
}

// Função utilitária para unir dois conjuntos x e y
// Utiliza a técnica de União por Rank
void uniao(struct subconjunto subconjuntos[], int x, int y) {
    int raizX = buscar(subconjuntos, x);
    int raizY = buscar(subconjuntos, y);

    // Anexa a árvore de menor rank à raiz da árvore de maior rank
    if (subconjuntos[raizX].rank < subconjuntos[raizY].rank) {
        subconjuntos[raizX].pai = raizY;
    } else if (subconjuntos[raizX].rank > subconjuntos[raizY].rank) {
        subconjuntos[raizY].pai = raizX;
    } else {
        // Se os ranks forem iguais, escolhe um como raiz e incrementa seu rank
        subconjuntos[raizY].pai = raizX;
        subconjuntos[raizX].rank++;
    }
}

// Compara duas arestas de acordo com seus pesos (Usado no qsort)
int compararArestas(const void* a, const void* b) {
    struct Aresta* a1 = (struct Aresta*)a;
    struct Aresta* b1 = (struct Aresta*)b;
    return a1->peso > b1->peso;
}

// Função principal do Algoritmo de Kruskal
void KruskalAGM(struct Grafo* grafo) {
    int V = grafo->V;
    struct Aresta resultado[V]; // Vetor para armazenar a AGM final
    int e = 0; // Índice usado para o vetor resultado[]
    int i = 0; // Índice usado para iterar nas arestas ordenadas

    // Passo 1: Ordenar todas as arestas em ordem não-decrescente de peso
    qsort(grafo->aresta, grafo->E, sizeof(grafo->aresta[0]), compararArestas);

    // Alocar memória para criar V subconjuntos
    struct subconjunto* subconjuntos = (struct subconjunto*) malloc(V * sizeof(struct subconjunto));

    // Criar subconjuntos contendo um único elemento para cada vértice
    for (int v = 0; v < V; ++v) {
        subconjuntos[v].pai = v;
        subconjuntos[v].rank = 0;
    }

    // Passo 2: Iterar pelas arestas ordenadas
    // A AGM terá exatamente V - 1 arestas
    while (e < V - 1 && i < grafo->E) {
        // Pega a menor aresta e incrementa o índice para a próxima iteração
        struct Aresta prox_aresta = grafo->aresta[i++];

        int x = buscar(subconjuntos, prox_aresta.origem);
        int y = buscar(subconjuntos, prox_aresta.destino);

        // Se a inclusão desta aresta não formar um ciclo (se eles pertencem a conjuntos diferentes),
        // inclui a aresta no resultado e une os dois conjuntos.
        if (x != y) {
            resultado[e++] = prox_aresta;
            uniao(subconjuntos, x, y);
        }
        // Caso contrário (x == y), descarte a aresta
    }

    // Exibir o resultado
    printf("Arestas selecionadas para a Arvore Geradora Minima (AGM):\n");
    printf("Origem -- Destino == Peso\n");
    printf("-------------------------\n");
    
    int custoTotal = 0;
    for (i = 0; i < e; ++i) {
        printf("  %d    --    %d    ==  %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
        custoTotal += resultado[i].peso;
    }
    printf("-------------------------\n");
    printf("Custo total da AGM: %d\n", custoTotal);

    // Liberar memória
    free(subconjuntos);
}

// Função Principal
int main() {
    /* Grafo de exemplo:
       V = 4 vértices (0, 1, 2, 3)
       E = 5 arestas
       
          10
      0--------1
      |  \     |
     6|   5\   |15
      |      \ |
      2--------3
          4       
    */
    int V = 4; 
    int E = 5; 
    struct Grafo* grafo = criarGrafo(V, E);

    // Aresta 0-1
    grafo->aresta[0].origem = 0;
    grafo->aresta[0].destino = 1;
    grafo->aresta[0].peso = 10;

    // Aresta 0-2
    grafo->aresta[1].origem = 0;
    grafo->aresta[1].destino = 2;
    grafo->aresta[1].peso = 6;

    // Aresta 0-3
    grafo->aresta[2].origem = 0;
    grafo->aresta[2].destino = 3;
    grafo->aresta[2].peso = 5;

    // Aresta 1-3
    grafo->aresta[3].origem = 1;
    grafo->aresta[3].destino = 3;
    grafo->aresta[3].peso = 15;

    // Aresta 2-3
    grafo->aresta[4].origem = 2;
    grafo->aresta[4].destino = 3;
    grafo->aresta[4].peso = 4;

    // Executa Kruskal
    KruskalAGM(grafo);

    // Liberar memória do grafo
    free(grafo->aresta);
    free(grafo);

    return 0;
}