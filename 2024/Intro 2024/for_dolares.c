#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    short dolares_conv;
    long pesos_resultado_libre;
    long pesos_resultado_oficial;
    short cot_ofi = 980;
    short cot_libre = 1340;
    short respuesta = 0;
    short contador = 0;

    printf("\e[1m Quiere ingresar una operacion? \e[m 0=Si / 1=No: ");
    scanf("%hd",&respuesta);

    while(respuesta==0 && contador<3)
    {
        printf("\v\tIngrese la cantidad de dolares a comprar: ");
        scanf("%hd",&dolares_conv);

        if(dolares_conv <= 5000)
        {
            pesos_resultado_libre = dolares_conv * cot_libre;
            pesos_resultado_oficial = dolares_conv * cot_ofi;

            printf("\tPrecio $%ld en cotizacion libre \n", pesos_resultado_libre);
            printf("\tPrecio $%ld en cotizacion oficial \n", pesos_resultado_oficial);
            printf("\tDiferencia / Ganancia $%ld  \n", pesos_resultado_libre - pesos_resultado_oficial);

            if(dolares_conv>1000)
            {
                contador = contador + 1;
                printf("\tContador = %hd\n", contador);
            }

            if(pesos_resultado_oficial>500000)
            {
                printf("\tEsta operacion sera notificada a AFIP por superar los $500000. \n");
            }
        }
        else
        {
            printf("\tNo se permiten operaciones de venta mayores a 5000 dolares. \n");
        }

        if(contador<3)
        {
            printf("\nQuiere ingresar una nueva operacion? 0=Si / 1=No: ");
            scanf("%hd",&respuesta);
        }
        else
        {
            printf("\nNo se permiten mas operaciones!\n");
        }
    }

    printf("\nGracias por usar arbolito-system\n");

    return 0;
}
