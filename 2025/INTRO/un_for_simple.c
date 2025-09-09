#include <stdio.h>

int main() {

    // Veamos el ultimo de los ciclos, el ciclo FOR
    // El ciclo for es igual a los anteriores, pero con la siguiente diferencias
    // Generalmente lo vas a usar cuando ya sabes la cantidad de cosas que tenes que hacer.
    // Usamos while cuando no sabemos cuanto dura el bucle, usamos for cuando si sabemos cuando dura el bucle, el for tambien se usa para recorrer los array.
    
    // Supongamos que nos piden sumar los numeros enteros del 1 al 20 con un lazo FOR
    
    short suma=0;
    for (short i = 1; i < 21; i++) // i++ es un contador
    {
        suma = suma + i; // Suma es un ACUMULADOR
        printf("La suma da: %hd \n",suma);
    }
    
    printf("Fin! \n");

    return 0;
}
