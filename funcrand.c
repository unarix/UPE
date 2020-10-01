#include <stdio.h>
#include <stdlib.h>

short genRandom();

int main()
{
    short i = 0;

    while(i<10)
    {
        printf("el generado aleatorio es: %hd \n",  genRandom());
        i = i + 1;
    }
    
    return 0;
}

short genRandom()
{
    return rand();
}