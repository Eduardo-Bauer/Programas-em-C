//algoritmo "S001_S00000200"
// Autor : baueredu
// Data : 03/08/2023
#include <stdio.h>
void main()
{
         float v1, v2, area;
         printf ("Qual o valor da base do triangulo?\n");
         scanf ("%f", &v1);
         printf ("Qual o valor da altura do triangulo?\n");
         scanf ("%f", &v2);
         area = (v1*v2)/2;
         printf ("O valor da área do triangulo é %f", area);
}
