
#include <stdio.h>
//Vamos a sumar dos numeros

void sumar_con_puntero(short *p, short *q, short, short);

int mainx ()
{
    short numero = 5;
    short n2;
    short n1;

    //printf("El valor de numero es: %hd \n", numero);
    //sumar_con_puntero(&numero);
    //printf("El valor de numero es: %hd \n", numero);
    //sumar_con_puntero(&numero);
    //printf("El valor de numero es: %hd \n", numero);

    sumar_con_puntero(&n1,&n2,5,7);

    printf("El valor de n1 es: %hd \n", n1);
    printf("El valor de n2 es: %hd \n", n2);

    return 0;
}

void sumar_con_puntero(short *p, short *q, short a, short b)
{
    *p = *p + *p; // Es lo mismo que hacer n1 = n1 + n1;
    *q = a - b;
}
