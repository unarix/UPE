#include <stdio.h>
#include <stdlib.h>

//https://gist.github.com/vratiu/9780109 <-- Codigos de colores y demas...

void numColor(short, short);
void separador(void);
void limpiarPantalla(void);

int main()
{
    printf("Bienvenido\n");
    separador();

    numColor(1,1);
    numColor(2,55);
    limpiarPantalla();
    numColor(5,76);
    numColor(4,44);

    return 0;
}

void numColor(short color, short numero)
{
    printf("\033[0;3%hdm",color);
    printf("El numero es: %hd\n", numero);
    printf("\033[0m");
    separador();
}

void separador(void)
{
    printf("-------------------\n");
}

void limpiarPantalla(void)
{
    system("pause");
    system("cls");
}
