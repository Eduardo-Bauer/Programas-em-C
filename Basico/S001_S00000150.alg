//algoritmo "S001_S00000150"
// Autor : baueredu
// Data : 03/08/2023
#include <stdio.h>
void main()
{
         float nota1, nota2, nota3, media;
         printf ("valor da primeira nota:\n");
         scanf ("%f", &nota1);
         printf ("valor da segunda nota:\n");
         scanf ("%f", &nota2);
         printf ("valor da terceira nota:\n");
         scanf ("%f", &nota3);
         media = (nota1+nota2+nota3)/3;
         printf ("A média do aluno é %f", media);
}
