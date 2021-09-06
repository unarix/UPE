
#include <stdio.h>

void filtro_limite(short *vector, short limite, short ); // Prototipo

int mainx()
{
    short vector[] = {10,22,33,55,11,77,66,99,88};
    short cantidad=sizeof(vector)/sizeof(short); //Calculamos la cantidad de posiciones que tiene el vector.

    //Imprimir el vector original
    for(int i=0;i<cantidad;i++)
    {
        printf(" Posicion: %hd - Valor: %hd \n", i, vector[i]);
    }

    printf("\n Ahora lo voy a ordenar: \n\n");
    filtro_limite(&vector, 25, cantidad);

    for(int i=0;i<cantidad;i++)
    {
        printf(" Posicion: %hd - Valor: %hd \n", i, vector[i]);
    }

    return 0;
}

// la funcion filtra los valores por encima del limite enviado por parametro
void filtro_limite(short *vector, short limite, short cantidad)
{
    int i=0;

    while(i<=cantidad)
    {
        if(vector[i]>limite)
        {
            vector[i] = limite;
        }
        i++;
    }
}
