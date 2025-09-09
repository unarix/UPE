#include <stdio.h>

//Hacé un programa que pida al usuario ingresar dos números enteros: un valor inicial y un valor final.
//Luego, usá un bucle for para imprimir todos los números entre esos dos valores.

// Los alumnos suelen asumir que siempre se empieza de menor a mayor, por lo tanto escriben algo como:
// for (int i = inicio; i <= fin; i++) { ... }

int main() {
    short inicio;
    short fin;

    printf("Ingrese el valor inicial: ");
    scanf("%hd", &inicio);

    printf("Ingrese el valor final: ");
    scanf("%hd", &fin);

    if (inicio <= fin) {
        for (int i = inicio; i <= fin; i++) {
            printf("%hd ", i);
        }
    } else {
        // Si los valores están al revés, el bucle debe ir hacia atrás
        for (int i = inicio; i >= fin; i--) {
            printf("%hd ", i);
        }
    }

    printf("\n");
    return 0;
}
