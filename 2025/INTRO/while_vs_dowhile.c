#include <stdio.h>

// Solicitarle al usuario que ingrese un numero y sumarlo hasta que el usuario indique que ya no quiere ingresar mas

int main() {
    int numero;
    int suma = 0;
    char continuar;

    printf("Desea ingresar un numero? (s/n): ");
    scanf(" %c", &continuar);

    while (continuar == 's' || continuar == 'S') {
        printf("Ingrese un numero: ");
        scanf("%d", &numero);

        suma += numero;

        printf("Desea ingresar otro número? (s/n): ");
        scanf(" %c", &continuar);
    }

    printf("\nLa suma total es: %d\n", suma);

    return 0;
}

// es mejor con Do while! no repetimos codigo.

#include <stdio.h>

int main() {
    int numero;
    int suma = 0;
    char continuar;

    do {
        printf("Ingrese un número: ");
        scanf("%d", &numero);

        suma += numero;

        printf("¿Desea ingresar otro número? (s/n): ");
        scanf(" %c", &continuar);  // el espacio antes de %c evita problemas con el Enter

    } while (continuar == 's' || continuar == 'S');

    printf("\nLa suma total es: %d\n", suma);

    return 0;
}

