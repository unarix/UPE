#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    short i=0;
    
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


    return 0;
}
