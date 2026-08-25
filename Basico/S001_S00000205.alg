//algoritmo "S001_S00000205"
// Autor : baueredu
// Data : 06/08/2023
#include <stdio.h>
void main()
{
         float xa, ya, xb, yb, xc, yc, ab, bc, ac;
         printf ("Qual o valor de x de A?\n");
         scanf ("%f", &xa);
         printf ("Qual o valor de y de A?\n");
         scanf ("%f", &ya);
         printf ("Qual o valor de x de B?\n");
         scanf ("%f", &xb);
         printf ("Qual o valor de y de B?\n");
         scanf ("%f", &yb);
         printf ("Qual o valor de x de C?\n");
         scanf ("%f", &xc);
         printf ("Qual o valor de y de C?\n");
         scanf ("%f", &yc);
         ab = (yb-ya)/(xb-xa);
         bc = (yc-yb)/(xc-xb);
         ac = (yc-ya)/(xc-xa);
         printf ("o valor de AB é %f\n", ab);
         printf ("o valor de BC é %f\n", bc);
         printf ("o valor de AC é %f\n", ac);
}
