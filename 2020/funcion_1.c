#include <stdio.h>
#include <stdlib.h>

void prints();
short sumar(short n1, short n2);
void numColor(short color, short numero);

int main()
{
    numColor(33,1);
    numColor(34,2);
    numColor(35,3);
    numColor(36,4);

    printf("\033[0;%hdm", 33);
    printf("%hd \n", 1); 
    printf("\033[0m"); 

    printf("\033[0;%hdm", 34);
    printf("%hd \n", 2); 
    printf("\033[0m");

    printf("\033[0;%hdm", 35);
    printf("%hd \n", 3); 
    printf("\033[0m");

    printf("\033[0;%hdm", 36);
    printf("%hd \n", 4); 
    printf("\033[0m");

    //printf("El resultado de la suma es: %hd\n", sumar(1,2));
    //prints();
    return 0;
}

void numColor(short color, short numero)
{
    printf("\033[0;%hdm", color);
    printf("El num es: %hd \n", numero); 
    printf("\033[0m"); 
}

short sumar(short n1, short n2)
{
    return n1+n2;
}

void prints()
{
    printf("Hola como va?\n");
    printf("Como estas?\n");   
}