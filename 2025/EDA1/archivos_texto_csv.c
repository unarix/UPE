#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 256

int main() {
    FILE *archivo;
    char buffer[MAX_LINE];

    // 1. Escribir en el archivo CSV
    archivo = fopen("agenda.csv", "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para escribir");
        return 1;
    }

    // Escribir encabezado y algunos datos
    fputs("Nombre,Telefono,Email\n", archivo);
    fputs("Juan Perez,1234567890,juan@example.com\n", archivo);
    fputs("Ana Gomez,9876543210,ana@example.com\n", archivo);
    fputs("Carlos Ruiz,5551234567,carlos@example.com\n", archivo);

    fclose(archivo);

    // 2. Leer el archivo CSV
    archivo = fopen("agenda.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para lectura");
        return 1;
    }

    printf("Contenido del archivo agenda.csv:\n\n");

    while (fgets(buffer, MAX_LINE, archivo)) {
        printf("%s", buffer);  // fgets ya incluye el salto de línea
    }

    fclose(archivo);

    return 0;
}
