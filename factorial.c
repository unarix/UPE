#include <stdio.h>
#include <stdlib.h>

int main()
{
    short primero, segundo;
    
    printf("Ingrese el primer numero entero: ");
    scanf("%hd",&primero);
    
    printf("\nIngrese el segundo numero entero: ");
    scanf("%hd",&segundo);
    
    while(segundo <= primero)
    {
        printf("El segundo no es mayor que el primero");
    
        printf("\nIngrese de nuevo el segundo: ");
        scanf("%hd",&segundo);
    }

    return 0;
}
