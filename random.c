#include <stdio.h>
#include <stdlib.h> // <-- esta es la libreria que tiene la funcion rand
#include <time.h> // <-- esta es la libreria que tiene la funcion time

short genRandoms(short); // prototipo
short dados(short hasta, short desde);

int main()
{
    short numero;
    short i=0;

    srand(time(NULL)); // NO AGREGAR AL PRIMER EJER

    //printf("Aleatorio: %hd\n", genRandoms(20));

    // Ej 4:
    // while(i<10)
    // {
    //     printf("ingrese un numero para el random maximo: ");
    //     scanf("%hd",&numero);
    //     printf("Aleatorio: %hd\n", genRandoms(numero));
    //     i=i+1;
    // }

    i=1;
    //Ej 5:
    while(i<11)
    {
        printf("> Tirada %hd:\n", i);
        printf("  Dado 1: %hd\n", dados(6,1));
        printf("  Dado 2: %hd\n", dados(6,1));
        
        i++;
    }

    return 0;
}

short genRandoms(short N) // firma
{
    //srand (getpid());
    //return rand () % (HASTA-DESDE+1) + DESDE;   // Este está entre M y N
    return rand () % (N-10+1) + 10;   // Este está entre M y N
    //return rand() % (N+1);
}

short dados(short hasta, short desde)
{
    return rand () % (hasta-desde+1) + desde; 
}