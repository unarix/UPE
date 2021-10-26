#include <stdio.h>

// Vamos a crear un vector de 5 posiciones, donde vamos a guardar en cada posicion un numero que el
// usuario tiene que ingresar por teclado
// al finalizar, debemos imprimir lo siguiente:
// - Imprimir todos los valroes ingresados
// - La suma de todos ellos
// - El Promedio
// - El Porcentaje de valores mayores a 10

int main(void)
{
    short cant = 5;
    short A[cant]; // declaramos el vector de 5 posiciones.
    short i=0;

    while(i<cant)
    {
        printf("Ingrese valor para la pos %hd \n", i);
        scanf("%hd",&A[i]);
        i++;
    }
    
    i=0;

    // Imprimir todos los valores ingresados
    while(i<cant)
    { 
        printf("El valor de la pos %hd es: %hd \n", i, A[i]); 
        i++; 
    } 


    i=0; // Porque debo poner a i + a cero nuevamente? 
    short suma=0; // poner esto al inicio del programa

    // Imprimir la suma de todos
    while(i<cant)
    { 
        suma = suma + A[i];
        i++; 
    } 
    
    printf("La suma de todos es: %hd \n", suma); 

    // Promedio
    printf("El promedio es: %hd \n", suma / cant); 

    // Porcentaje
    i=0;
    short cant_may=0; // poner esto al inicio del programa

    // tengo que recorrer de nuevo todo el vector!!! 
    while(i<cant)
    { 
        if(A[i]>10)
            cant_may++;
        i++; 
    } 

    printf("El porcentaje de valores mayores a 10 es: %.2f% \n\n", (float)cant_may / (float)cant * 100.0);
    // AHORA! OPTIMICEMOS ESTE CODIGO! 
    // Explicar que es una refactorizacion del codigo
    // Como podemos mejorar los tiempos que tarda este codigo en ejecutarse?
    // Que es lo que mas tiempo tarda en este programa?


    return 0;
}