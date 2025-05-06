#include <stdio.h>
#include <unistd.h>
#include <time.h>

void imprimir_con_animacion(const char *texto, useconds_t retardo) {
    while (*texto) {
        putchar(*texto++);
        fflush(stdout);
        usleep(retardo);
        //sleep(retardo);
    }
    printf("\n");
}

int main() {
    imprimir_con_animacion("Hola, soy un texto que se esta escrbiendo de a poco, muy pioola!!!", 9000);
    printf("\n");
    return 0;
}