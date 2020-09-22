#include <stdio.h>
#include <stdlib.h>

//http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/

void printc(char*, short); // prototipo
void printn(short, short); // prototipo

int main()
{
    short i;
    
    printc("soy",31);
    printc("un",32);
    printc("estudiante",33);
    printc("de",34);
    printc("sistemas",35);

    for(i=30;i<50;i++)
    {
        printc("*",i);
    }

    printn(9,1);

    printf("\n");
    return 0;
}

void printc(char* texto, short color )
{
    printf("\033[0;%hdm", color);
    printf("%s", texto);
    printf("\033[0m "); //Reset a blanco
}

void printn(short numero, short color )
{
    switch(color)
    {
        case 1: // rojo
            printf("\033[0;41m");
            break;
        case 2: // amarillo
            printf("\033[0;43m");
            break;
        case 3: // verde
            printf("\033[0;42m");
            break;
    }
    printf("\n %hd \n", numero);
    printf("\033[0m"); //Reset a blanco
}
