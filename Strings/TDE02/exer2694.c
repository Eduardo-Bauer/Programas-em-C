#include <stdio.h>
#define N 15
int calculadora(char str[N]){
  int total=0, numero=0, i;
  for(i=0; str[i]!='\0';i++){
    if(str[i]>='1' && str[i]<='9'){
      numero += str[i]-'0';
      if(str[i+1]>='1' && str[i+1]<='9'){
        numero = numero*10;
      }else{
        total += numero;
        numero = 0;
      }
    }
  }
  return total;
}
int main() {
  char str[N];
  int n, i;
  scanf("%d", &n);
  getchar();
  for(i=0;i<n;i++){
    gets(str);
    printf("%d\n", calculadora(str));
  }
}