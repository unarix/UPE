#include <stdio.h>

// El while es como un if pero un if evalúa una condición una sola vez, en cambio el while la evalúa de forma repetitiva hasta que la condicion no sea verdadera.

// Ejemplo, Suma diez veces el numero 1, de uno en uno y guarde su resultado en una variable total.

int main() {
	short sumador = 0; // 1. Inicialización de la variable de control
	
	// Bueno, da la forma que podriamos hacerlo usando lo que sabemos es: 
	/*
	sumador = sumador + 1;
	sumador = sumador + 1;
	sumador = sumador + 1;
	sumador = sumador + 1;
	sumador = sumador + 1;
	sumador = sumador + 1;
	sumador = sumador + 1;
	sumador = sumador + 1;
	sumador = sumador + 1;
	*/
	
	// Una de las cosas para lo que me sirve el while es para ahorrarme codigo, repetir el codigo que esta dentro tantas veces como la condicion lo diga.
	// Condición de permanencia, mientras la condicion sea verdadera, ejecuta el codigo que esta dentro.
	while (sumador <= 10) {
		sumador = sumador + 1; // 3. Actualización (paso hacia el fin del bucle)
	}
	
	// Explicar el concepto de bucle infinito, no incrementando nunca el sumador.
	// la variable nunca cambia, la condición siempre es verdadera y el programa queda colgado consumiendo recursos.
	
	printf("Sumador = %hd \n", sumador);
	printf("¡Bucle terminado!\n");
	return 0;
}
