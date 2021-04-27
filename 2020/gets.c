#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char texto[10];
    gets(texto);
    fflush(stdin);
    printf("\n lo ingr es: %s",texto);
    return 0;
}
