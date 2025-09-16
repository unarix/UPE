#include <stdio.h>
#include <string.h>

// El bucle do...while asegura que se ejecuta al menos una vez.
// El usuario tiene hasta 3 intentos (intentos < 3).
// Se usa strcmp() para comparar la contraseña ingresada con la correcta.
// Si el usuario acierta, se marca accesoConcedido = 1 y se hace break para salir del bucle.
// Al finalizar, se muestra un mensaje de acceso concedido o denegado según el resultado.
// En cada ciclo, mostrarle al usuario cuantos reintentos le quedan.

int main() {
    char password[20];
    const char correctPassword[] = "pass123";
    int intentos = 0;
    int accesoConcedido = 0;

    do {
        printf("Ingrese la password: ");
        scanf("%19s", password);

        intentos = intentos + 1;

        if (strcmp(password, correctPassword) == 0) {
            accesoConcedido = 1;
            printf("Acceso concedido en el intento: %d\n", intentos);
            // break;  // No nos gusta que usen el break!
        } else {
            printf("Password incorrecta. Intentos restantes: %d\n", 3 - intentos , accesoConcedido);
        }

    } while (intentos < 3 && accesoConcedido != 1);

    if (accesoConcedido) {
        printf("Bienvenido al sistema!\n");
    } else {
        printf("Acceso denegado. Demasiados intentos fallidos.\n");
    }

    return 0;
}
