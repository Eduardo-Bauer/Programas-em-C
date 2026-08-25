#include <stdio.h>
#include <stdlib.h>

int le_e_menor(int N, int *menor){
  int i, pos;
  int *valores = (int*)malloc(N * sizeof(int));
  if(valores==NULL){
    printf("ERRO\n");
    exit(0);
  }
  for(i=0;i<N;i++){
    scanf("%d", &valores[i]);
    if(i==0){
      *menor = valores[i];
      pos = i;
    }else{
      if(*menor > valores[i]){
        *menor = valores[i];
        pos = i;
      }
    }
  }
  return pos;
}

int main() {
  int N, menor, pos;
  scanf("%d", &N);
  pos = le_e_menor(N, &menor);
  printf("Menor valor: %d\n", menor);
  printf("Posicao: %d\n", pos);
}