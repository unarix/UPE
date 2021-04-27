#include <stdio.h>
#include <stdlib.h> // <-- esta es la libreria que tiene la funcion rand
#include <time.h> // <-- esta es la libreria que tiene la funcion time

short genRandom(short); // prototipo
void genRandoms(short);
void colorRand(short N);

int main()
{
    short numero;
    short i=0;

    srand(time(NULL));

    printf("ingrese un numero para el random maximo: ");
    scanf("%hd",&numero);

    while(i<10)
    {
        genRandoms(numero);
        i=i+1;
    }
    
    return 0;
}

void colorRand(short N) // firma
{
    printf("\033[0;3%hdm", N); // cuerpo
    printf("%hd ", N);
    printf("\033[0m");
}

void genRandoms(short N) // firma
{
    //srand (getpid());
    colorRand(rand() % (N+1));
}