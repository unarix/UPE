
#include <stdio.h>

void ordenar ( short *vector, short cantidad); // Creamos una funcion y declaramos el paramtro puntero

int main()
{
    short vector[] = {10,6,22,33,55,11,77,66,99};
    short cantidad=sizeof(vector)/sizeof(short);

    //Imprimir el vector desordenado
    for(int i=0;i<cantidad;i++)
    {
        printf(" Posicion: %hd - Valor: %hd \n", i, vector[i]);
    }

    printf("\n Ahora lo voy a ordenar: \n\n");
    ordenar(&vector, cantidad);

    for(int i=0;i<cantidad;i++)
    {
        printf(" Posicion: %hd - Valor: %hd \n", i, vector[i]);
    }

    return 0;
}

// la funcion ordenar; ordena los valores del vector
void ordenar (short *vector, short cantidad)
{
    short aux;

    // Algoritmo burbuja
    for(int i=0;i<cantidad;i++)
    {
        for(int j=0;j<cantidad-1;j++)
        {
            if(vector[j]>vector[j+1])
            {
                aux=vector[j];
                vector[j]=vector[j+1];
                vector[j+1]=aux;
            }
        }
    }

}
