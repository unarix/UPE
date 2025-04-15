#include <stdio.h>

short buscar(short *vector, short cantidad, short valor); // Creamos una funcion y declaramos el paramtro puntero

int main()
{
    short vector[] = {10,6,22,33,55,11,77,66,99};
    short cantidad= sizeof(vector)/sizeof(short);

    //Imprimir el vector
    for(int i=0;i<cantidad;i++)
    {
        printf(" Posicion: %hd - Valor: %hd \n", i, vector[i]);
    }

    short valor = 0;
    printf("> Ingrese el valor a buscar secuencialmente: \n");
    scanf("%hd",&valor);

    short posicion = 0;
    posicion = buscar(&vector, cantidad, valor);

    if(posicion != -1)
        printf("\n El %hd fue encontrado en la posicion %hd\n",vector[posicion], posicion);
    else
        printf("\n No se encontro el valor\n");


    return 0;
}

// La funcion buscar, busca secuencialmente los valores
short buscar(short *vector, short cantidad, short valor)
{
    for (int i = 0; i < cantidad; i++) {
        if (vector[i] == valor) {
            return i; // Devuelve la posición donde se encontró
        }
    }
    return -1; // Si no se encuentra, devuelve -1
}

