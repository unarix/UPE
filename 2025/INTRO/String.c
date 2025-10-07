/*
¿Qué es un string en C?

En C, no existe un tipo de dato nativo llamado string como en otros lenguajes (Python, Java, etc.).
En su lugar, usamos un array de caracteres que termina con un carácter especial: '\0' (fin de cadena).

Consideraciones importantes sobre strings en C
  Los strings son arrays de tipo char que terminan con '\0'.
  scanf("%s", ...) no puede leer frases con espacios. Para eso se usa fgets() (más avanzado).
  Siempre hay que reservar un carácter más para el '\0'.
  C no tiene funciones como .length() o .concat() como otros lenguajes. Se usan funciones de <string.h> como:
  strlen()
  strcpy()
  strcat()
  strcmp()

*/

#include <stdio.h>

int main() {
    char nombre[50]; // Array de caracteres (string) con espacio para 49 letras + '\0'

    printf("Ingrese su nombre: ");
    scanf("%s", nombre); // Lee una palabra (hasta el primer espacio)

    printf("Hola, %s! Bienvenido al programa.\n", nombre);

    return 0;
}
