#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *infoTriangulo(short a,short b,short c);

int main(){

 short lado1,lado2,lado3;
 char  triangulo[15];
 char *resultado;


resultado = triangulo;
printf("\n Indique el primer lado del triangulo: ");
scanf("%hd",&lado1);

printf("\n Indique el segundo lado del triangulo: ");
scanf("%hd",&lado2);

printf("\n Indique el tercer lado del triangulo: ");
scanf("%hd",&lado3);

resultado = (char *) infoTriangulo(lado1,lado2,lado3);

printf("%s",resultado);

}

char *infoTriangulo(short a,short b,short c){

    static char triangulo[15];

    if(a == b & b == c)
    {
        strcpy(triangulo,"Equilatero");
        return triangulo;

    }
    else if ( a != b & b != c)
    {
        strcpy(triangulo,"Escaleno");
        return triangulo;

    }
    else
    { 
        strcpy(triangulo,"Isosceles");
        return triangulo;
    }
}












