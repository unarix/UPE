#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *infoTriangulo(short a,short b,short c);

int main()
{
    short lado1, lado2, lado3;
    char triao[15];
    char *triangulo;

    triangulo = triao;
    printf("\n Indique el primer lado del triangulo: ");
    scanf("%hd",&lado1);
    printf("\n Indique el segundo lado del triangulo: ");
    scanf("%hd",&lado2);
    printf("\n Indique el tercer lado del triangulo: ");
    scanf("%hd",&lado3);
    
    triangulo = (char *)infoTriangulo(lado1,lado2,lado3);

    printf("\n El triangulo es: %s \n", triangulo);

    return 0;
}

char *infoTriangulo(short a,short b,short c){
    
    static char triangulo[11];

    if(a == b & b == c){
        strcpy(triangulo,"Equilatero");
    }
    else if ( a != b & b != c)
    {
        //return printf("\n El triangulo es Escaleno");
        strcpy(triangulo,"Escaleno");
    }
    else
    { 
        //return printf("\n El triangulo es Isosceles");
        strcpy(triangulo,"Isosceles");
    }

    return triangulo;
}