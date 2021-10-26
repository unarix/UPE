#include <stdio.h>
// Vamos a crear un vector de 5 posiciones, donde vamos a guardar en cada posicion un numero que el
// usuario tiene que ingresar por teclado
// al finalizar, debemos imprimir lo siguiente:
// - Imprimir todos los valroes ingresados
// - La suma de todos ellos
// - El Promedio
// - El Porcentaje de valores mayores a 10
#define cant 10

int main(void)
{
    short A[cant];
    short i=0;
    short suma=0;
    short cont_may=0;

    while(i<cant)
    {
        printf("Ingrese el valor para la pos %hd \n", i);
        scanf("%hd",&A[i]);
        i++;
    }
    
    // Imprimir todos los val ingresados
    i=0;
    while(i<cant)
    {
        printf("el valor de la pos %hd es: %hd \n", i, A[i]);
        i++;
    }

    i=0;
    while(i<cant)
    {
        suma = suma + A[i];
        i++;
    }
    printf("La suma de todos los val del vector es %hd \n",suma);

    // Imprimiendo el promedio
    printf("El promedio es: %.2f \n", (float)suma/cant);

    for(i=0;i<cant;i++)
    {
        if(A[i]>10)
        {
            cont_may++;
        }
    }

    

    printf("El porcentaje de valores mayores a 10 es: %f \n\n", (float)cont_may / cant * 100);

    return 0;
}