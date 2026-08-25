#include <stdio.h>
#define N 102
int contador(char str[N]){
  int i;
  for(i=0;str[i]!='\0';i++);
  return i;
}
void decifra(char str[N]){
  int i, tamanho = contador(str)-1, j=0;
  char novo[N];
  for(i=tamanho/2; i>=0; i--){
    novo[j++] = str[i];
  }
  for(i=tamanho; i>tamanho/2; i--){
    novo[j++] = str[i];
  }
  novo[j] = '\0';
  printf("%s\n", novo);
}
int main() {
  int i, n;
  char str[N];
  scanf("%d", &n);
  getchar();
  for(i=0;i<n;i++){
    gets(str);
    decifra(str);
  }
}