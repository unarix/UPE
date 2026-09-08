// Escribir un programa en C que simule el acceso a un cajero automático. El PIN correcto guardado en el sistema es 1234.
// El programa debe solicitar al usuario que ingrese su clave PIN.
// Si la clave es incorrecta, debe mostrar un mensaje de error y volver a pedirla.
// El ciclo solo debe terminar cuando el usuario ingrese la clave correcta.
// Al acertar, debe mostrar un mensaje de "¡Acceso concedido!".

#include <stdio.h>

int main() {
    int pin_correcto = 1234;
    int pin_ingresado;

    printf("=====================================\n");
    printf("          CAJERO AUTOMATICO          \n");
    printf("=====================================\n");

    // 1. Primera lectura fuera del bucle
    printf("Ingrese su clave PIN: ");
    scanf("%d", &pin_ingresado);

    // 2. Condición: Mientras el PIN sea INCORRECTO, repetimos
    while (pin_ingresado != pin_correcto) {
        printf("[ERROR] Clave incorrecta. Intente nuevamente: ");
        scanf("%d", &pin_ingresado); // 3. Actualización de la variable dentro del bucle
    }

    // 4. Salida del bucle (solo ocurre si la condición del while se vuelve falsa)
    printf("\n¡Acceso concedido! Bienvenido a su cuenta.\n");

    return 0;
}
