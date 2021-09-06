#include <stdio.h>

int main()
{
    short a, b, c;

    printf("\n Indique el primer lado del triangulo: ");
    scanf("%hd",&a);
    printf("\n Indique el segundo lado del triangulo: ");
    scanf("%hd",&b);
    printf("\n Indique el tercer lado del triangulo: ");
    scanf("%hd",&c);
    
    if(a == b && b == c)
    {
        printf("El triangulo es Equilatero\n");
    }
    else 
    {
        if (a!= b && b!=c && a!=c)
        {
            printf("El triangulo es Escaleno\n");
        }
        else
        { 
            printf("El triangulo es Isosceles\n");
        }
    }

    return 0;
}