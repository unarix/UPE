#include <stdio.h>

// VAMOS A HACER EL ULTIMO EJ PARA QUE SE VEA UNA APLICACION SENCILLA.
// QUEREMOS HACER UNA FUNCION QUE INTERCAMBIE EL VALOR DE NUESTRAS VARIABLES EN EL MAIN

void intercambia (short *, short *); // NOTAR QUE NO HACE FALTA PONER LA VAR PERO SI EL TIPO!!!!

int main ()
{
    // declaración de variables a utilizar
    short a = 10;
    short b = 5;

    // impresión de resultados
    printf("El valor de A es: %hd \n",a);
    printf("El valor de B es: %hd \n",b);

    // llamado a función
    printf("\n\nLlamar a la funcion intercambia\n");
    intercambia(&a,&b);

    // impresión de resultados
    printf("El valor de A es: %hd \n",a);
    printf("El valor de B es: %hd \n",b);

    return 0;
}

void intercambia (short *ptrnro1, short *ptrnro2)
{
    short aux= *ptrnro1;
    *ptrnro1= *ptrnro2;
    *ptrnro2= aux;
}

