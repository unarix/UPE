#include <stdio.h>


int imp_color(short num, short color, short separar)
{
    printf("\033[0;%hdm",color);
    printf("%hd ",num); 
    printf("\033[0m");
    
    int pepe = 2;

    static short numeros = 0;
    //numeros=0;

    printf("Numeros %hd\n",numeros);
    numeros++;

    int local;
    global=1;

    if(separar==1)
    {
        separador();
    }
}