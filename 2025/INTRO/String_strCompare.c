#include <stdio.h>
#include <string.h> // Necesario para usar strcmp()

/* ingrese dos cadenas de caracteres y comparelas 

¿Qué hace strcmp()?
    strcmp(cadena1, cadena2) compara carácter por carácter.
    esta dentro de la libreria <string.h>
Como trabaja?
    Compara dos cadenas carácter por carácter, utilizando el código ASCII de cada letra.
    Paso a paso explicado:
        Compara el primer carácter de cada string.
        Si son iguales, pasa al siguiente.
        Repite esto hasta encontrar una diferencia o llegar al final ('\0').
    Si encuentra una diferencia:
        Resta los códigos ASCII de los caracteres actuales.
        Devuelve ese resultado:
            0 → las cadenas son iguales
            >0 → el primer carácter distinto en s1 es mayor que el de s2
            <0 → el carácter en s1 es menor que el de s2
    
*/

// Definición de estructura (Primero no hacer con estrcutura, hacer al final)
struct persona {
    char nombre[50];
    char apellido[50];
    char nombreCompleto[100];
};

int main() {
    char cadena1[100];
    char cadena2[100];

    // Pedir al usuario que ingrese dos cadenas
    printf("Ingrese la primera cadena: ");
    scanf("%s", cadena1);

    fflush(stdin); //Limpia el buffer!

    printf("Ingrese la segunda cadena: ");
    scanf("%s", cadena2);

    // Comparar las cadenas usando strcmp()
    if (strcmp(cadena1, cadena2) == 0) {
        printf("Las cadenas son iguales.\n");
    } else {
        printf("Las cadenas son diferentes.\n");
    }

    // Mostrar la longitud de cada cadena
    printf("\nLongitud de la primera cadena: %lu caracteres\n", strlen(cadena1));
    printf("Longitud de la segunda cadena: %lu caracteres\n", strlen(cadena2));

    // String Cat: Concatena dos cadenas de caracteres (las une)
    strcat(cadena1, cadena2);
    printf("La union es: %s \n", cadena1);

    // Str Copy:
    char copia[100];
    strcpy(copia, cadena1);
    printf("La copia es: %s \n", cadena1);

    // Con estructuras:
    struct persona p;

    // Ingreso de datos
    printf("Ingrese el nombre: ");
    scanf("%s", p.nombre);

    printf("Ingrese el apellido: ");
    scanf("%s", p.apellido);

    // Construcción del nombre completo
    strcpy(p.nombreCompleto, p.nombre);     // Copiar nombre
    strcat(p.nombreCompleto, " ");          // Agregar espacio
    strcat(p.nombreCompleto, p.apellido);   // Agregar apellido

    // Mostrar nombre completo
    printf("\nNombre completo: %s\n", p.nombreCompleto);

    // Mostrar longitud
    printf("Longitud del nombre completo: %lu caracteres\n", strlen(p.nombreCompleto));

    // Comparación de nombre con "Juan"
    if (strcmp(p.nombre, "Juan") == 0) {
        printf("El nombre ingresado es Juan.\n");
    } else {
        printf("El nombre ingresado no es Juan.\n");
    }


}
