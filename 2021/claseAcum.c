#include <stdio.h>

int main()
{
    int contador = 0;
    int acumulador = 0;
    int edad;
    int i=0;
    float promedio;
    int min=99;
    int max=0;

    while(i<5)
    {
        printf("Ingrese la edad de la persona que ingresa: \n");
        scanf("%d",&edad);

        if(edad>=18)
        {
            contador = contador + 1;
        }

        if(edad<min)
            min = edad;
        if(edad>max)
            max = edad;

        acumulador = acumulador + edad;
        
        i++;
    }

    promedio = (float)acumulador / i;

    printf("Las personas mayores son: %d \n", contador);
    printf("La acumulacion de edades es: %d \n", acumulador);
    printf("El promedio de edad es: %.2f \n", promedio);
    printf("La edad minima es: %d \n", min);
    printf("La edad maxima es: %d \n", max);

    return 0;
}