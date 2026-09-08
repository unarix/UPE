#include <stdio.h>

// El while es como un if pero un if evalúa una condición una sola vez, en cambio el while la evalúa de forma repetitiva hasta que la condicion no sea verdadera.

// Ejemplo, Suma diez veces el numero 1, de uno en uno y guarde su resultado en una variable total.

int main() {
    int sumador = 1; // 1. Inicialización de la variable de control

    sumador = sumador + 1;
    sumador = sumador + 1;
    sumador = sumador + 1;
    sumador = sumador + 1;
    sumador = sumador + 1;
    sumador = sumador + 1;
    sumador = sumador + 1;
    sumador = sumador + 1;
    sumador = sumador + 1;
    
    // 2. Condición de permanencia
    while (contador <= 10) {
        sumador = sumador + 1; // 3. Actualización (paso hacia el fin del bucle)
    }

    printf("¡Bucle terminado!\n");
    return 0;
}
