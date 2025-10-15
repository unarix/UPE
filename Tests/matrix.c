#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>     // para usleep()
#include <string.h>

#define ANCHO 80
#define ALTO 25

int main() {
    char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%&";
    int columnas[ANCHO];
    
    // Inicialización
    srand(time(NULL));
    memset(columnas, 0, sizeof(columnas));

    // Bucle infinito para simular la animación
    while (1) {
        for (int y = 0; y < ALTO; y++) {
            for (int x = 0; x < ANCHO; x++) {
                // Determinar si se imprime un carácter o un espacio
                if (rand() % 10 > 2) {
                    char c = chars[rand() % (sizeof(chars) - 1)];
                    printf("\033[1;32m%c\033[0m", c);  // Verde brillante
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        usleep(100000);  // Pausa entre "frames"
        printf("\033[H"); // Mover el cursor al inicio (sin limpiar pantalla)
    }

    return 0;
}
