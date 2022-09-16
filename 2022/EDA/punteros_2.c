#include <stdio.h>

int main()
{
    // Vamos a ver cuanto ocupan los punteros:

    // Creamos tres variables, una float y las otras de tipo char y string
    float a = 2.66;
    char b = 'X';
    char texto[] = {"Hola mundo \n"};

    // Ahora creamos los punteros a esas variables:
    float *puntero_uno;
    char *puntero_dos;

    // Ahora asignamos a esos punteros las direcciones de las variables que vamos a hacer referencia
    puntero_uno = &a;
    puntero_dos = &b;
    // NOTAR QUE NO PONGO EL * cuando asigno!!!
    // es FUNDAMENTAL asignar los punteros ya que de otra forma obtengo un puntero descontrolado.

    // Veamos entonces ahora cuanto ocupan los punteros:

    printf("\nTamanio puntero a float: %hd\n", sizeof(puntero_uno));
    printf("Tamanio puntero a char: %hd\n\n", sizeof(puntero_dos));
    // EJECUTAR!
    // ESTO QUIERE DECIR QUE LOS PUNTEROS SIEMPRE OCUPAN 8BYTES EN PROCESADORES 64BITS Y 4 EN 32BITS

    // Para verificar lo dicho, imprimo la cantidad de bytes que ocupa cada una de mis variables
    printf("Tamanio del float: %hd\n", sizeof(a));
    printf("Tamanio del char: %hd\n", sizeof(b));
    printf("Tamanio del texto: %hd\n\n",sizeof(texto));
    // EJECUTAR!
    // Los valores son correctos! porque el texto ocupa solo 1? porque es la primera direccion la que cuenta.
    // El fin lo marca el null.

    // Ahora imprimo los contenidos de las variables usando y no usando punteros
    printf("Contenido de lo apuntado por p1: %f y contenido del float %f\n", *puntero_uno,a);
    printf("Contenido de lo apuntado por p2: %c y contenido del char %c\n\n", *puntero_dos,b);

    // Por ultimo veamos la imprecion del texto
    puntero_dos = texto;
    // A alguien se le ocurre proque no pongo el amperson?
    // No se pone el amperson porque TEXTO es una array con lo cual ya es una direcion de memoria que apunta a su primer elemento.

    printf("Texto: %s", puntero_dos);

    return 0;
}

