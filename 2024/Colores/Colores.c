#include <stdio.h>

int main()
{
    // Codigos colores
    // https://gist.github.com/vratiu/9780109

    printf("\033[1;30m");
    printf("Hola 0 \n");
    printf("\033[1;31m");
    printf("Hola 1 \n");
    printf("\033[1;32m");
    printf("Hola 2 \n");
    printf("\033[1;33m");
    printf("Hola 3 \n");
    printf("\033[4;32m");
    printf("Underline 2 \n");
    printf("\033[4;36m");
    printf("Underline 6 \n");
    printf("\033[41;32m");
    printf("Background 1 Text 2\n");
    printf("\033[42;31m");
    printf("Background 2 Text 1\n");

    printf("\033[0;93m");
    printf("Bold High Intensty 93 \n");
    printf("\033[0;94m");
    printf("Bold High Intensty 94 \n");
    // Vuelvo al color default.
    //printf("\033[0m");

    return 0;
}
