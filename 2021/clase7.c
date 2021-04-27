#include <stdio.h>

void imp_color(short, short, short);
void separador();

short global;
int pepe = 1;

int main()
{
    // printf("\033[0;31m");
    // printf("1"); 
    // printf("\033[0m");
    // printf("\033[0;32m");
    // printf("2"); 
    // printf("\033[0m");
    // printf("\033[0;33m");
    // printf("3\n"); 
    // printf("\033[0m");
    // printf("\033[0;34m");
    // printf("4\n"); 
    // printf("\033[0m");
    // printf("\033[0;35m");
    // printf("5\n"); 
    // printf("\033[0m");

    for(int i=20;i<41;i++)
    {
        imp_color(i,i,0);
    }



    global=2;

    printf("\n");

    return 0;
}

void imp_color(short num, short color, short separar)
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

void separador()
{
    printf("\n");
}