#include <stdio.h>
#include <string.h>
#define N 100

struct fruta{
  char fruta[50];
  float preco;
}typedef FRUTA;

struct comprar{
  char fruta[50];
  int quant;
}typedef COMPRA;

void le_fruta(FRUTA f[N], int total){
  int i;
  for(i=0;i<total;i++){
    scanf("%s %f", f[i].fruta, &f[i].preco);
  }
}

void le_comprar(COMPRA c[N], int frutas){
  int i;
  for(i=0;i<frutas;i++){
    scanf("%s %d", c[i].fruta, &c[i].quant);
  }
}

void comparador(FRUTA f[N], int total, COMPRA c[N], int frutas){
  int i, j;
  float preco=0;
  for(i=0;i<total;i++){
    for(j=0;j<frutas;j++){
      if(strcasecmp(f[i].fruta, c[j].fruta)==0){
        preco = preco + f[i].preco * c[j].quant;
      }
    }
  }
  printf("R$ %.2f\n", preco);
}

int main() {
  int i, n, total, frutas;
  FRUTA f[N];
  COMPRA c[N];
  scanf("%d", &n);
  for(i=0;i<n;i++){
    scanf("%d", &total);
    le_fruta(f, total);
    scanf("%d", &frutas);
    le_comprar(c, frutas);
    comparador(f, total, c, frutas);
  }
}