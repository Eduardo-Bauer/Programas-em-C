/*
Implementar o algoritmo de Dijkstra, que imprima:

a) o valor do menor caminho entra um nodo origem e todos os demais nodos;

b) a sequência de vértices que forma o caminho mínimo de um nodo origem até os demais nodos;

c) o caminho mínimo de um nodo origem até um nodo destino.
*/

#include <stdio.h>
#define INFINITY 9999
#define MAX 10

// Declaração das funções
void Dijkstra(int Graph[MAX][MAX], int n, int start, int dest);
void printPath(int start, int target, int pred[]);

// Função recursiva para imprimir o caminho da origem até o destino
void printPath(int start, int target, int pred[]) {
    if (target == start) {
        printf("%d", start);
        return;
    }
    printPath(start, pred[target], pred);
    printf(" -> %d", target);
}

void Dijkstra(int Graph[MAX][MAX], int n, int start, int dest) {
  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // Criando a matriz de custos
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];

  // Inicializando os vetores de distância, predecessores e visitados
  for (i = 0; i < n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  // Algoritmo de Dijkstra para encontrar os menores caminhos
  while (count < n - 1) {
    mindistance = INFINITY;

    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode; // Salva o nodo anterior para reconstruir o caminho
        }
    count++;
  }

  // a) O valor do menor caminho entre um nodo origem e todos os demais nodos
  printf("--- a) Custo do menor caminho do nodo origem %d para os demais ---\n", start);
  for (i = 0; i < n; i++) {
    if (i != start) {
      if (distance[i] < INFINITY)
        printf("Custo para o nodo %d: %d\n", i, distance[i]);
      else
        printf("Custo para o nodo %d: Inalcancavel\n", i);
    }
  }

  // b) A sequência de vértices que forma o caminho mínimo de um nodo origem até os demais
  printf("\n--- b) Sequencia de vertices do nodo %d para os demais ---\n", start);
  for (i = 0; i < n; i++) {
    if (i != start) {
      if (distance[i] < INFINITY) {
        printf("Caminho para o nodo %d: ", i);
        printPath(start, i, pred);
        printf("\n");
      } else {
        printf("Caminho para o nodo %d: Sem caminho disponivel\n", i);
      }
    }
  }

  // c) O caminho mínimo de um nodo origem até um nodo destino específico
  if (dest >= 0 && dest < n && dest != start) {
    printf("\n--- c) Caminho minimo do nodo origem %d ate o nodo destino %d ---\n", start, dest);
    if (distance[dest] < INFINITY) {
      printf("Custo Total: %d\n", distance[dest]);
      printf("Sequencia: ");
      printPath(start, dest, pred);
      printf("\n");
    } else {
      printf("O nodo %d e inalcancavel a partir do nodo %d.\n", dest, start);
    }
  }
}

int main() {
  int Graph[MAX][MAX], n, u, dest;
  n = 7;

  Graph[0][0] = 0; Graph[0][1] = 0; Graph[0][2] = 1; Graph[0][3] = 2; Graph[0][4] = 0; Graph[0][5] = 0; Graph[0][6] = 0;
  Graph[1][0] = 0; Graph[1][1] = 0; Graph[1][2] = 2; Graph[1][3] = 0; Graph[1][4] = 0; Graph[1][5] = 3; Graph[1][6] = 0;
  Graph[2][0] = 1; Graph[2][1] = 2; Graph[2][2] = 0; Graph[2][3] = 1; Graph[2][4] = 3; Graph[2][5] = 0; Graph[2][6] = 0;
  Graph[3][0] = 2; Graph[3][1] = 0; Graph[3][2] = 1; Graph[3][3] = 0; Graph[3][4] = 0; Graph[3][5] = 0; Graph[3][6] = 1;
  Graph[4][0] = 0; Graph[4][1] = 0; Graph[4][2] = 3; Graph[4][3] = 0; Graph[4][4] = 0; Graph[4][5] = 2; Graph[4][6] = 0;
  Graph[5][0] = 0; Graph[5][1] = 3; Graph[5][2] = 0; Graph[5][3] = 0; Graph[5][4] = 2; Graph[5][5] = 0; Graph[5][6] = 1;
  Graph[6][0] = 0; Graph[6][1] = 0; Graph[6][2] = 0; Graph[6][3] = 1; Graph[6][4] = 0; Graph[6][5] = 1; Graph[6][6] = 0;

  u = 0;       // Nodo de origem
  dest = 5;    // Escolha de um nodo destino para demonstrar o item 'c'

  Dijkstra(Graph, n, u, dest);

  return 0;
}