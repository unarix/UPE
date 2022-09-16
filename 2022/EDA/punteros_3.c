#include <stdio.h>

// Vamos a hacer un ejersicio en el cual 
// queremos que una funcion resuelva una cuenta de suma pero que no retorne nada.
// Que era el ambito de una funcion??
// basicamente queremos que en nuestro MAIN nos modifique desde afuera las variables. 


// Creamos el prototipo
void sumapuntero(short *p);

int main()
{
    // Creamos una variable que tiene un valor para poder sumar:
    short numero = 5;


    // HACER AHORA LA FUNCION
    // ******



    // AHORA VAMOS A IMPRIMR EL VALOR DE NUESTRO NUMERO
    printf("El valor de nuestro numero es: %hd \n",numero);

    // AHORA VAMOS A LLAMAR A LA FUNCION SUMA, PASANDOLE AL PUNTERO LA DIRECCION DE NUESTRA VARIABLE
    // NOTAR QUE PASAMOS LA DIRECCION DE LA VARIABLE!!!!
    sumapuntero(&numero);

    printf("El nuevo valor de numero es %hd \n", numero);

    return 0;
}

void sumapuntero(short *p)
{
    *p = *p + *p;
}

