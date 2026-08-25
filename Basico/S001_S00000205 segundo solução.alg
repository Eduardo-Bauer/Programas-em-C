//algoritmo "S001_S00000205"
// Autor : baueredu
// Data : 06/08/2023
#include <stdio.h>
void main()
{
         float xa, ya, xb, yb, xc, yc, ab, bc, ac;
         printf ("Qual digites os valores em ordem, xy de A, xy de B e xy de C?\n");
         scanf ("%f%f%f%f%f%f", &xa, &ya, &xb, &yb, &xc, &yc);
         ab = (yb-ya)/(xb-xa); 
         bc = (yc-yb)/(xc-xb); 
         ac = (yc-ya)/(xc-xa);
         printf ("o valor de AB é %f, BC é %f, AC é %f\n", ab, bc, ac);
}
