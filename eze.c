#include <stdio.h>
#include <stdlib.h>

void numColor(short color, short numero);

int main()
{
    short i=1;

    while(i<101)
    {
        numColor(i,i);
        i = i + 1;
    }
    
    printf("\n");

    return 0;
}

void numColor(short color, short numero)
{
    printf("\033[0;%hdm", color);
    printf("%hd ", numero);
    printf("\033[0m");
}