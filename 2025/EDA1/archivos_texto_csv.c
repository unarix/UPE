#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 256

int main() {
    FILE *archivo;
    // No explicar al principio.
    char buffer[MAX_LINE];

    // Ahora lo que necesitamos es abrir el archivo.
    // Cual era el modo que si no existia lo crea? "WT"
    // como hacia esto?
    archivo = fopen("agenda.csv", "wt");

    // Siempre que abro un archivo necesito comprobar el acceso, como lo hago?
    if (archivo == NULL) {
        perror("Error al abrir el archivo para escribir");
        return 1;
    }

    // Entonces yo voy a intentar escribir en mi archivo CSV datos que estan separados por comas
    // Que funcion me permite poner texto en mi archivo? FPUTS()
    // Escribir encabezado y algunos datos
    fputs("Nombre,Telefono,Email\n", archivo);
    fputs("Juan Perez,1234567890,juan@example.com\n", archivo);
    fputs("Ana Gomez,9876543210,ana@example.com\n", archivo);
    fputs("Carlos Ruiz,5551234567,carlos@example.com\n", archivo);

    // Correr el programa!
    // Mirar el archivo!
    // Esta todo ok?

    // Entonces ahora vamos a leerlo.
    // que tengo que hacer si se que voy a necesitar en el mismo programa volver a abrir el archivo?
    fclose(archivo);

    // 2. Leer el archivo CSV
    archivo = fopen("agenda.csv", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para lectura");
        return 1;
    }

    printf("Contenido del archivo agenda.csv:\n\n");

	fgets(buffer, MAX_LINE, archivo);
    while (!feof(archivo)) {
        printf("%s", buffer);  // fgets ya incluye el salto de línea
		fgets(buffer, MAX_LINE, archivo);
    }

    // Supongamos que llegue quiero volver a leer? como puedo hacer para rebovinar?
    rewind(archivo);  // Volver al principio del archivo

    printf("Leyendo de nuevo desde el principio:\n\n");

	fgets(buffer, MAX_LINE, archivo);
    while (!feof(archivo)) {
        printf("%s", buffer);  // fgets ya incluye el salto de línea
		fgets(buffer, MAX_LINE, archivo);
    }

    fclose(archivo);

    return 0;

}
