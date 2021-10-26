#include <stdio.h>
#include <stdlib.h>

int main()
{

    // printf("%d \n",1);
    // printf("%d \n",2);
    // printf("%d \n",3);
    // printf("%d \n",4);
    // printf("%d \n",5);

    short primer_numero = 0;
    short segundo_numero = 0;

    printf("Ingrese el primer numero: ");
    scanf("%hd",&primer_numero);

    printf("Ingrese el segundo numero: ");
    scanf("%hd",&segundo_numero);

    while(segundo_numero <= primer_numero)
    {
        if(segundo_numero == primer_numero)
            printf("es igual");
        else
            printf("El numero %hd es mayor que %hd \n",primer_numero,segundo_numero);
        

        printf("Ingrese el segundo numero: ");
        scanf("%hd",&segundo_numero);
    }

    printf("Fin del programa");

    return 0;
}