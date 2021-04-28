#include <stdio.h>
#include <stdlib.h>

int main()
{

    short *puntero_a_entero;

    printf("\nCrearemos un espacio para almacenar un entero \n");
    printf("y lo haremos en TIEMPO DE EJECUCION \n\n");

    puntero_a_entero=(short *)malloc(sizeof(short));

    printf("Ahora le damos un valor desde teclado: ");
    scanf("%hd",puntero_a_entero);

    printf("\nlo ingresado fue: %hd\n\n",  *puntero_a_entero);

    printf("...y ahora lo eliminamos de memoria\n");
    printf("lo haremos haciendo free(puntero_a_entero)\n");
    puntero_a_entero=NULL;
    
    free((short *)puntero_a_entero);
    
    if(puntero_a_entero!=NULL)
        printf("\nlo ingresado fue: %hd\n\n",*puntero_a_entero);
    else
        printf("el puntero no existe!!\n\n");

    return 0;
}