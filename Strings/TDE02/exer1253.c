#include <stdio.h>
#define N 51
void cripto(char str[N], int varia){
  int i;
  for(i=0; str[i]!='\0';i++){
    if(str[i] - 'A' - varia < 0){
      str[i] = 'Z' - varia + 1 + (str[i]-'A');
    }else{
      str[i] = str[i] - varia;
    }
  }
  printf("%s\n", str);
}
int main() {
  char str[N];
  int varia, repetir, i;
  scanf("%d", &repetir);
  getchar();
  for(i=0;i<repetir;i++){
    gets(str);
    scanf("%d", & varia);
    getchar();
    cripto(str, varia);
  }
}