#include <stdio.h>
#include <string.h>

struct persona {
    char nombre[50];
    int edad;
};

int main() {
    int cantidad, i;

    struct persona actual;
    struct persona mayor;
    struct persona menor;

    printf("Cuantas personas vas a ingresar?: ");
    scanf("%d", &cantidad);

    for (i = 0; i < cantidad; i++) {
        printf("\nPersona %d:\n", i + 1);

        printf("Nombre: ");
        scanf(" %[^\n]", actual.nombre); // Permite leer nombres con espacios

        printf("Edad: ");
        scanf("%d", &actual.edad);

        // En la primera persona, inicializamos "mayor" y "menor"
        if (i == 0) {
            mayor = actual;
            menor = actual;
        } else {
            if (actual.edad > mayor.edad) {
                mayor = actual;
            }

            if (actual.edad < menor.edad) {
                menor = actual;
            }
        }
    }

    // Mostrar resultados
    printf("\nPersona de MAYOR edad:\n");
    printf("Nombre: %s\n", mayor.nombre);
    printf("Edad: %d\n", mayor.edad);

    printf("\nPersona de MENOR edad:\n");
    printf("Nombre: %s\n", menor.nombre);
    printf("Edad: %d\n", menor.edad);

    return 0;
}
