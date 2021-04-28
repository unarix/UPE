#include <stdio.h>
#include <stdlib.h>

// Crear un programa que me permita generar un vector dinamico solicitandole al usuario la cantidad de posiciones que va a tener. 
// Luego llenar esas posiciones con numeros para finalmente imprimirlos

int main()
{
    short *ptr;
    short cantidad;
    short i;

    printf("Ingresar un numero de elementos para el vector \n");
    scanf("%hd",&cantidad);

    ptr = (short*)malloc(cantidad * sizeof(short));

    if (ptr == NULL)
    {
        printf("La memoria no fue reser correctamente \n");
        
    }
    else
    {
        printf("La memoria fue alocada correctamente \n");

        for(i=0; i<cantidad; i++)
        {
            ptr[i] = i+1;
        }

        printf("Los elementos del array son: \n");
        
        for(i=0; i<cantidad; i++)
        {
            printf("%hd - ", ptr[i]);
        }
        
        printf("\n");

        ptr = NULL;
        free(ptr);
    }

    return 0;
}