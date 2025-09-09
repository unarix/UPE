#include <stdio.h>

// Diferencia entre While y Do While

int main() {
    int valor = 10;

    printf("Con WHILE:\n");
    while (valor < 5) {
        printf("Esto no se imprime porque la condición es falsa.\n");
    }

    printf("\nCon DO...WHILE:\n");
    do {
        printf("Esto se imprime al menos una vez, aunque la condición sea falsa.\n");
    } while (valor < 5);

    return 0;
}
