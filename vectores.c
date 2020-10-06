#include <stdio.h>
#include <stdlib.h>

int main()
{

    // Ej 1
    short i=0;
    // short A[10];

    // while(i<10)
    // {
    //     A[i] = rand() % 10;
    //     i++;
    // }

    // i=0;

    // printf("El valor de la pos %hd es %hd \n", 1, A[1]);
    // printf("El valor de la pos %hd es %hd \n", 6, A[6]);
    // printf("El valor de la pos %hd es %hd \n", 8, A[8]);

    // Ej 2
    // while(i<10)
    // {
    //     printf("El valor de la pos %hd es %hd \n", i, A[i]);
    //     i++;
    // }

    // Ej 3
    short B[5];
    i=0;
    while(i<5)
    {
        printf("Ingrese valor para la pos %hd \n", i);
        scanf("%hd",&B[i]);
        i++;
    }
    
    i=0;
    while(i<5)
    {
        printf("El valor de la pos %hd es %hd \n", i, B[i]);
        i++;
    }

    // Ej 4
    i=0;
    short ant=999;
    while(i<5)
    {
        if(ant>B[i])
            ant = B[i];
        
        i++;
    }

    printf("El valor minimo es: %hd \n", ant);

    return 0;
}
