#include <stdio.h>
/*
¿Por qué do...while es ideal acá?
Siempre queremos que el menú se muestre al menos una vez.
Luego, se sigue mostrando hasta que el usuario elija la opción de salida (3 en este caso).
Permite manejar entradas inválidas sin repetir código.
*/

int main() {
    int opcion;

    do {
        printf("\n=== MENÚ PRINCIPAL ===\n");
        printf("1. Ver información\n");
        printf("2. Configuración\n");
        printf("3. Salir\n");
        printf("Seleccione una opción (1-3): ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Mostrando información...\n");
                break;
            case 2:
                printf("Entrando en configuración...\n");
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }

    } while (opcion != 3);

    return 0;
}
