#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Realice un programa que pida tres números por teclado e indique cuál es el
    //mayor de los tres (en caso de que los tres números sean iguales también debe
    //indicarlo).

    short a=0;
    short b=0;
    short c=0;
    short result=0;
//
//
//    printf("Ingrese num1: \n");
//    scanf("%hd",&a);
//    printf("Ingrese num2: \n");
//    scanf("%hd",&b);
//    printf("Ingrese num3: \n");
//    scanf("%hd",&c);
//
//    if(a>b)
//        result = a;
//    else
//        result = b;
//
//    if(c>result)
//        result = c;
//
//    printf("El mayor es: %hd \n",result);


    //Mejore el ejercicio anterior para que el programa nos indique si los numeros
    //ingresados son los tres iguales, si hay dos iguales o si son los tres distintos.
//    printf("Ingrese num1: \n");
//    scanf("%hd",&a);
//    printf("Ingrese num2: \n");
//    scanf("%hd",&b);
//    printf("Ingrese num3: \n");
//    scanf("%hd",&c);
//
//    short count=0;
//    if(a>b)
//    {
//        result = a;
//    }
//    else
//        result = b;
//
//    if(c>result)
//    {
//        result = c;
//    }
//
//    if(a==b)
//        count = 2;
//    if(a==b && b==c)
//        count = 3;
//
//    printf("El mayor es: %hd \n",result);
//    printf("Hay %hd numeros iguales. \n",count);

//    printf("\n Indique el primer lado del triangulo: ");
//    scanf("%hd",&a);
//    printf("\n Indique el segundo lado del triangulo: ");
//    scanf("%hd",&b);
//    printf("\n Indique el tercer lado del triangulo: ");
//    scanf("%hd",&c);
//
//    if(a == b && b == c)
//    {
//        printf("El triangulo es Equilatero\n");
//    }
//    else
//    {
//        if (a!= b && b!=c && a!=c)
//        {
//            printf("El triangulo es Escaleno\n");
//        }
//        else
//        {
//            printf("El triangulo es Isosceles\n");
//        }
//    }
//

    short dolares_conv;
    long pesos_resultado_libre;
    long pesos_resultado_oficial;
    short cot_ofi = 980;
    short cot_libre = 1340;

    printf("Ingrese la cantidad de dolares a comprar: \n");
    scanf("%hd",&dolares_conv);

    if(dolares_conv <= 1000)
    {
        pesos_resultado_libre = dolares_conv * cot_libre;
        pesos_resultado_oficial = dolares_conv * cot_ofi;

        printf("Precio $%ld en cotizacion libre \n", pesos_resultado_libre);
        printf("Precio $%ld en cotizacion oficial \n", pesos_resultado_oficial);
        printf("Diferencia / Ganancia $%ld  \n", pesos_resultado_libre - pesos_resultado_oficial);

        if(pesos_resultado_oficial>500000)
        {
            printf("Esta operacion sera notificada a AFIP por superar los $500000. \n");
        }
    }
    else
    {
        printf("No se permiten operaciones de venta mayores a 1000 dolares. \n");
    }



    return 0;

    return 0;
}
