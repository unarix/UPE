#include <stdio.h>
#include <stdlib.h>

int main()
{
    short numero;
    short anterior=0;

    printf("Ingrese el numero");
    scanf("%hd",&numero);

    while(numero>anterior)
    {
        anterior = numero;
        printf("Ingrese un numero mayor");
        scanf("%hd",&numero);
    }

    printf("Termino porque no era mayor.");

    return 0;
}
