#include <stdio.h>
#include <string.h>

// El bucle do...while asegura que se ejecuta al menos una vez.
// El usuario tiene hasta 3 intentos (intentos < 3).
// Se usa strcmp() para comparar la contraseña ingresada con la correcta.
// Si el usuario acierta, se marca accesoConcedido = 1 y se hace break para salir del bucle.
// Al finalizar, se muestra un mensaje de acceso concedido o denegado según el resultado.

int main() {
    char password[20];
    const char correctPassword[] = "clave123";
    int intentos = 0;
    int accesoConcedido = 0;

    do {
        printf("Ingrese la contraseña: ");
        scanf("%19s", password);

        if (strcmp(password, correctPassword) == 0) {
            accesoConcedido = 1;
            break;  // Salimos del bucle si la contraseña es correcta
        } else {
            printf("Contraseña incorrecta. Intentos restantes: %d\n", 2 - intentos);
        }

        intentos++;

    } while (intentos < 3);

    if (accesoConcedido) {
        printf("¡Acceso concedido!\n");
    } else {
        printf("Acceso denegado. Demasiados intentos fallidos.\n");
    }

    return 0;
}
