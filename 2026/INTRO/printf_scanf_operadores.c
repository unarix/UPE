#include <stdio.h>

int main() {
    // Aca el tipo de dato es un short
    short edad;

    printf("Ingrese su edad: ");
    scanf("%hd", &edad);

    // Evaluación con operadores relacionales y el operador lógico AND (&&)
    puede_subir = (edad >= 14);

    printf("\n--- ACCESO A LA Montania Rusa ---\n");
    printf("Resultado (1 = Autorizado / 0 = Denegado): %d\n", puede_subir);

    return 0;
}
