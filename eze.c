#include <stdio.h>
#include <stdlib.h>

void numColor(short color, short numero); // prototipo

int main()
{
    short i=1;

    while(i<101) // llamo varias veces a la funcion
    {
        numColor(i,i); // llamada a la funcion
        i = i + 1; // incremento
    }
    
    printf("\n"); //lo agrego solo par acrear un salto de linea

    return 0;
}

void numColor(short color, short numero) // firma
{
    printf("\033[0;%hdm", color); // cuerpo
    printf("%hd ", numero);
    printf("\033[0m");
}