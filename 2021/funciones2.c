#include <stdio.h>

void imp_color(short, short, short);
void separador();

short numeros2 = 0;

//https://www.theurbanpenguin.com/4184-2/
int main()
{
    // Nos piden imprimir en pantalla todos los codigos de colores
    // (en windows se hace de otra forma)
    printf("\033[0;31m"); 
    printf("1"); 
    printf("\033[0m"); 

    printf("\033[0;32m"); 
    printf("2"); 
    printf("\033[0m"); 

    printf("\033[0;33m"); 
    printf("3"); 
    printf("\033[0m"); 

    printf("\033[0;34m"); 
    printf("4");  
    printf("\033[0m"); 

    // Vamos a hacer una funcion que me ahorre escribir tantas veces lo mismo
    separador();
    imp_color(155,33,0);
    separador();

    // Vamos a averiguar cuantos codigos de colores existen
    for(int i=20;i<41;i++)
    {
        imp_color(i,i,0);
    }
    separador();

    printf("Numeros2= %hd\n",numeros2);
}

// Si agrego otra funcion con el mismo nombre no puedo, C no permite sobrecarga
void imp_color(short num, short color, short separar)
{
    printf("\033[0;%hdm",color); 
    printf("%hd ",num);  
    printf("\033[0m"); 

    // Supongamos que quiero extender para separar los numeros
    if(separar==1)
    {
        separador();
    }

    // VARIABLES ESTATICAS, GLOBALES, LOCALES Y EXTERNAS
    static short numeros;
    numeros = 0;
    printf("Numeros: %hd\n",numeros);
    numeros++;

    //EXTERNAS
    extern short numeros2;
    numeros2++;

}

void separador()
{
    printf("\n");
}