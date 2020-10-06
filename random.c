#include <stdio.h>
#include <stdlib.h> // <-- esta es la libreria que tiene la funcion rand
#include <time.h> // <-- esta es la libreria que tiene la funcion time

short genRandoms(short); // prototipo

int main()
{
    short numero;
    short i=0;

    //srand(time(NULL)); // NO AGREGAR AL PRIMER EJER

    printf("Aleatorio: %hd\n", genRandoms(20));

    // while(i<10)
    // {
    //     printf("ingrese un numero para el random maximo: ");
    //     scanf("%hd",&numero);
    //     printf("Aleatorio: %hd\n", genRandoms(numero));
    //     i=i+1;
    // }
    
    return 0;
}

short genRandoms(short N) // firma
{
    //srand (getpid());
    //return rand () % (HASTA-DESDE+1) + DESDE;   // Este está entre M y N
    return rand () % (N-10+1) + 10;   // Este está entre M y N
    //return rand() % (N+1);
}