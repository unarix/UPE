
#include <stdio.h>

void sumapuntero ( int *puntero_nro ); // Creamos una funcion y declaramos un parametro tipo puntero

int main()
{
    short numero = 5; // declaramos la variable numero y la igualamos a 5

    printf("El valor original de numero es %hd", numero);
    sumapuntero ( &numero ); //Llamo a la funcion y le envio la direccion de memoria (con el &) de numero.
    printf("El nuevo valor de numero es %hd", numero);
    return 0;
}

// la funcion sumapuntero; va a sumar los valores de la variable enviada como referencia 
void sumapuntero (int *puntero_nro) 
{
    *puntero_nro = *puntero_nro + *puntero_nro;
}

