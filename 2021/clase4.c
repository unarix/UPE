#include <stdio.h>

int main()
{
    // *******************************************************************************************************
    // Supongamos que tenemos que contar la cantidad de gente que entra a un museo. Nuestro primer contador
    // *******************************************************************************************************

    int contador = 0;
    int i = 0;

    while(i < 11)
    {
        contador = contador + 1;
        i++;
    }
    printf("El valor del contador es: %d \n",contador);

    // *******************************************************************************************************
    // Contar los que entran al museo y los mayores de 18 (usar el contador sin igualarlo a CERO)
    // *******************************************************************************************************
    contador = 0;
    int edad = 0;
    i = 1;
    int mayores = 0;

    while(i <= 10)
    {
        printf("Ingrese la edad de la persona  \n");
        scanf("%d",&edad);

        contador = contador + 1;
        if(edad>=18)
            mayores = mayores + 1;
        
        i++;
    }
    printf("El valor del contador es: %d \n",contador);
    printf("La cantidad de personas mayores es: %d \n",mayores);


    // *******************************************************************************************************
    // Nuestro primer acumulador - Cual es la edad acumulada?
    // *******************************************************************************************************

    int acumulador = 0;
    i = 1;
    int valor= 0;

    while(i<=10)
    {
        printf("Ingrese un valor para ser acumulado: \n");
        scanf("%d", &valor);

        acumulador = acumulador + valor;
        i++;
    }

    printf("El valor del acumulador es: %d \n", acumulador);

    // *******************************************************************************************************
    // Nuestra primera busqueda de maximos y minimos / cual fue la edad minimia y cual la edad maxima
    // *******************************************************************************************************

    valor = 0;
    int min = 0; //9999;
    int max = 0;
    int prim = 1;

    printf("Ingrese un valor positivo (negativo para finalizar) \n");
    scanf("%d",&valor);

    while(valor>=0)
    {
        // Explicar al final
        // if(prim==1)
        // {
        //     min = valor;
        //     max = valor;
        //     prim=0;
        // }

        if(valor<min)
            min = valor;
        if(valor>max)
            max = valor;

        printf("Ingrese un valor positivo (negativo para finalizar) \n");
        scanf("%d",&valor);
    }

    printf("El maximo es %d y el minimo es %d \n",max,min);

    // *******************************************************************************************************
    // Promedio: obtener el promedio de edad!
    // *******************************************************************************************************

    

}