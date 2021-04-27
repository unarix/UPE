#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    short A[5];
    short i = 0;
    srand(time(NULL));

    while(i<5)
    {
        printf("Ingrese valor para la pos %hd \n", i);
        scanf("%hd",&A[i]);
        i++;
    }
    
    i=0;

    while(i<5)
    { 
        printf("El valor de la pos %hd es: %hd \n", i, A[i]); 
        i++; 
    } 
    return 0;
}
