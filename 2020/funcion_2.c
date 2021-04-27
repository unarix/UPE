#include <stdio.h>
#include <stdlib.h>

short sumar(short n1, short n2); //prototipo

int main()
{
    printf("El resultado es %hd \n", sumar(2,3)); //llamada
    return 0;
}

short sumar(short n1, short n2) //implementacion
{
    return n1+n2;
}