#include <stdio.h>
#include <strings.h>
#define N 501

struct pais{
  char nome[50];
  int ouro;
  int prata;
  int bronze;
} typedef PAIS;

void le_pais(PAIS p[N], int cont){
  int i;
  for(i=0;i<cont;i++){
    scanf("%s %d %d %d", p[i].nome, &p[i].ouro, &p[i].prata, &p[i].bronze);
  }
}

void organizacao(PAIS p[N], int cont){
  int i, j;
  PAIS aux;
  for(i=0;i<cont;i++){
    for(j=0;j<cont-1;j++){
      if(p[j].ouro < p[j+1].ouro){
        aux = p[j];
        p[j] = p[j+1];
        p[j+1] = aux;
      }else{
        if(p[j].ouro == p[j+1].ouro && p[j].prata < p[j+1].prata){
          aux = p[j];
          p[j] = p[j+1];
          p[j+1] = aux;
        }else{
          if(p[j].ouro == p[j+1].ouro && p[j].prata == p[j+1].prata && p[j].bronze < p[j+1].bronze){
            aux = p[j];
            p[j] = p[j+1];
            p[j+1] = aux;
          }
        }
      }
    }
  }
  for(i=0;i<cont;i++){
    for(j=0;j<cont-1;j++){
      if(p[j].ouro == p[j+1].ouro && p[j].prata == p[j+1].prata && p[j].bronze == p[j+1].bronze && strcasecmp(p[j].nome, p[j+1].nome)>0){
        aux = p[j];
        p[j] = p[j+1];
        p[j+1] = aux;
      }
    }
  }
}

void escreve(PAIS p[N], int cont){
  int i;
  for(i=0;i<cont;i++){
    printf("%s %d %d %d\n", p[i].nome, p[i].ouro, p[i].prata, p[i].bronze);
  }
}

int main() {
  PAIS p[N];
  int cont;
  scanf("%d", &cont);
  le_pais(p, cont);
  organizacao(p, cont);
  escreve(p, cont);
}