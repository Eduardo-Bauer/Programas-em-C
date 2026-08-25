#include <stdio.h>
#include <stdlib.h>

int queda(int N){
  int i, anterior, queda=0;
  int *valores = (int*)malloc(N * sizeof(int));
  if(valores == NULL){
    printf("ERRO\n");
    exit(0);
  }
  for(i=0;i<N;i++){
    scanf("%d", &valores[i]);
  }
  anterior = valores[0];
  for(i=1;i<N;i++){
    if(anterior > valores[i]){
      queda = i;
      break;
    }
    anterior = valores[i];
  }
  return queda;
}

int main() {
  int N;
  scanf("%d", &N);
  int valor = queda(N);
  if(valor==0){
    printf("%d\n", valor);
  }else{
    printf("%d\n", valor+1);
  }
}