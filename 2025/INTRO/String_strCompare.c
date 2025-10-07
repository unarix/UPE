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

int main() {
    char cadena1[100];
    char cadena2[100];

    // Pedir al usuario que ingrese dos cadenas
    printf("Ingrese la primera cadena: ");
    scanf("%s", cadena1);

    printf("Ingrese la segunda cadena: ");
    scanf("%s", cadena2);

    // Comparar las cadenas usando strcmp()
    if (strcmp(cadena1, cadena2) == 0) {
        printf("Las cadenas son iguales.\n");
    } else {
        printf("Las cadenas son diferentes.\n");
    }

    return 0;
}
