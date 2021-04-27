#include <stdio.h>

int main()
{
    int contador=0;
    int edad = 0;
    int mayores = 0;
    int acumulador_edades = 0;
    int edad_menor = 0;
    int edad_mayor = 0;
    int flag=0;
    float promedio_edad=0;
    int continuar;

    printf("Quiere ingresar una persona? (0=NO / 1=SI)");
    scanf("%d",&continuar);

    while(continuar>=2 || continuar<0)
    {
        printf("Opcion incorrecta! \n");
        printf("Quiere ingresar una persona? (0=NO / 1=SI)");
        scanf("%d",&continuar);
    }

    while(continuar==1)
    {
        printf("Ingrese la edad de la persona: \n");
        scanf("%d",&edad);
        contador = contador + 1;
        if(edad>17)
        {
            //mayores = mayores + 1;
            mayores++;
        }

        //if(flag==0)
        if(contador==1)
        {
            edad_menor = edad;
            edad_mayor = edad;
            //flag=1;
        }

        if(edad<edad_menor)
        {
            edad_menor = edad;
        }
        if(edad>edad_mayor)
        {
            edad_mayor = edad;
        }

        acumulador_edades+=edad;
        
        printf("Quiere ingresar una persona? (0=NO / 1=SI)");
        scanf("%d",&continuar);
        while(continuar>=2 || continuar<0)
        {
            printf("Opcion incorrecta! \n");
            printf("Quiere ingresar una persona? (0=NO / 1=SI)");
            scanf("%d",&continuar);
        }
    }

    promedio_edad = (float)acumulador_edades / contador;

    printf("La cantidad de personas es: %d \n",contador);
    printf("La cantidad de mayores es de: %d \n",mayores);
    printf("Las edades acumuladas son: %d \n",acumulador_edades);
    printf("La menor edad es: %d\n",edad_menor);
    printf("La mayor edad es: %d\n",edad_mayor);
    printf("El promedio de edades es: %.2f \n", promedio_edad);

    return 0;
}

