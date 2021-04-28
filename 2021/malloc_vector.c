#include <stdio.h>
#include <stdlib.h>

// Crear un programa que me permita generar un vector dinamico solicitandole al usuario la cantidad de posiciones que va a tener. 
// Luego llenar esas posiciones con numeros contiguos para finalmente imprimierlos en una nueva linea

int main()
{
  
    // Este puntero va a almacenar la direc inicial del bloque creado
    short *ptr;
    short i;
    short numero;
  
    // Obtener el numero de elementos
    printf("Ingresar un numero de elementos:\n");
    scanf("%hd",&numero);

    // alocacion de memoria para el vector dinamicamente usando malloc
    ptr = (short*)malloc(numero * sizeof(short));
  
    // Check si la memoria fue alocada satisfactoriamente o no
    if (ptr == NULL) {
        printf("Memoria no alocada correctamente por falta de espacio.\n");
        exit(0);
    }
    else {
        // La memoria fue reservada correctamente
        printf("Memoria alocada correctamente.\n");
  
        // llenar los elementos del array
        for (i = 0; i < numero; ++i) {
            ptr[i] = i + 1;
        }
  
        // Imprimir los elementos del array
        printf("Los elementos del array son: ");
        for (i = 0; i < numero; ++i) {
            printf("%d, ", ptr[i]);
        }
        printf("\n");
    }
  
    return 0;
}