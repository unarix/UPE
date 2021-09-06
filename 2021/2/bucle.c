#include <stdio.h>
#include <stdlib.h>

int main()
{
    short suma;
    short numero;
    short nro_ant; 
    short i;
    short limite;
    
    // printf("\n Ingrese el limite: ");
    // scanf("%hd",&limite);

    // for(i=0; i<limite; i++)
    // {
    //     printf("\n Ingrese un numero: ");
    //     scanf("%hd",&numero);

    //     if(numero < nro_ant)
    //         printf("No es mayor");
    //     else
    //         printf("Es mayor");

    //     nro_ant = numero;
    // }

    // Diferencias entre while y do while

    i=10;

    while (i<10)
    {
        printf("\n con while: %hd", i++);
    }
    
    i=10;

    do
    {
        printf("\n con do while: %hd", i++);
    } while (i<10);
        

    // Solicitar que sume al menos una vez independientemente de que la suma supere limite

    printf("\n Ingrese el limite: ");
    scanf("%hd",&limite);

    do
    {
        printf("\n Ingrese el nro: ");
        scanf("%hd",&numero);

        suma = suma + numero;

    } while (suma>limite);


    return 0;
}
