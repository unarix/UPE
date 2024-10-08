//Vamos a crear un vector de 5 posiciones, donde vamos a guardar en cada posición un numero que el usuario tiene que ingresar por teclado.
//Al finalizar, debemos imprimir lo siguiente:
// - Imprimir todos los valroes ingresados
// - La suma de todos ellos
// - El Promedio
// - imprimir todos los valores mayores al promedio

#include <stdio.h> 
 
#define CANT 5 
 
int main(void) 
{ 
    short datos[CANT]; 
    short indice=0; 
    float prom; 
    short suma =0; 
 
    while(indice<CANT) 
    { 
        printf("Ingrese el valor para la pos %hd \n", indice); 
        scanf("%hd",&datos[indice]); 
        suma = suma + datos[indice]; 
        indice++; 
    } 
 
    printf("\n La suma de todos los valores del vector es: %hd \n", suma); 
 
    prom = (float)suma / CANT; 
    printf("El promedio es: %.2f", prom); 
 
    // Imprimr todos los valores del vector que superan al promedio 
    for(indice = 0; indice<CANT; indice++) 
    { 
        if(datos[indice]>prom) 
        { 
            printf("\n Numero mayor a prom: %hd \n", datos[indice]); 
        } 
    } 
 
    return 0; 
}
