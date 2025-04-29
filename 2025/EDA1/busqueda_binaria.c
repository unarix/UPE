// Busqueda binaria:
// Es un algoritmo que sirve para buscar un elemento dentro de un arreglo ordenado. 
// Es mucho más rápido que buscar uno por uno, porque va dividiendo el arreglo a la mitad en cada paso.
// El arreglo debe estar ordenado (por ejemplo, de menor a mayor).

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    short vector[ ]={2,4,5,6,9,12,15};
    short buscado, medio, superior, inferior;

    do{
        superior= (sizeof(vector) / sizeof(short)) -1;
        inferior= 0;
        medio= superior / 2;

        printf("\nIngrese valor a buscar: ");
        scanf("%hd", &buscado);

        while((vector[medio] != buscado) && (superior >= inferior))
        {
            if(buscado > vector[medio])
            {
                inferior = medio + 1;
            }
            else
            {
                superior = medio - 1;
            }

            medio = (superior + inferior) / 2;
        }

        if(buscado == vector[medio])
        {
            printf("Encontrado en %hd \n", medio);
        }
        else
        {
            printf("No existe \n");
        }

        printf("\n Presione s para continuar: ");
    }
    while(getch() == 's');

    return 0;
}
