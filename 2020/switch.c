#include <stdio.h>
#include <stdlib.h>

int main()
{
    short color=0;

    printf("\n Ingrese el nro: ");
    scanf("%hd",&color);

    switch(color)
    {
        case 1: // rojo
            printf("\033[0;41m");
            break;
        case 2: // amarillo
            printf("\033[0;43m");
            break;
        case 3: // verde
        case 4: // verde
            printf("\033[0;42m");
            break;
        default:
            printf("Nada");
    }
    
    printf("\n                                                           \n\n");

    printf("\033[0m"); //Reset a blanco
    return 0;
}

// Imagine que se tiene una maquina expendedora de caramelos y acepta billetes hasta 100$ 
// La maquina debe devolver el cambio en billetes de menor denominación. 

