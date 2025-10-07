#include <stdio.h>
#include <string.h> // Necesario para usar strcmp()

/* ingrese dos cadenas de caracteres y comparelas */

int main() {
    char cadena1[100];
    char cadena2[100];

    // Pedir al usuario que ingrese dos cadenas
    printf("Ingrese la primera cadena: ");
    scanf("%s", cadena1);

    printf("Ingrese la segunda cadena: ");
    scanf("%s", cadena2);

    // Comparar las cadenas usando strcmp()
    if (strcmp(cadena1, cadena2) == 0) {
        printf("Las cadenas son iguales.\n");
    } else {
        printf("Las cadenas son diferentes.\n");
    }

    return 0;
}
