#include <stdio.h>

int main()
{
    // Bueno gente, vamos a ver lo que son los punteros...
    // El puntero es un tema facil de entender pero es dificil de usar, y hay que estar atentos al usarlo.
    // El puntero se usa mucho en C y C++... en algunos otros lenguajes si bien no se usan mucho a nivel de codigo, el propio lenguaje generalmente
    // tiene un mecanismo que lo termina utilizando por debajo.

    // Un puntero es simplemente un tipo de dato que su finalidad es apuntar
    // a una direccion de memoria. 

    // Para que se entienda hagaos un dibujo... a ver si me sale...

    short variable=5; //declaro una variable cualquiera y le asigno un valor
    short *puntero; // declaro un puntero... el asterisco identifica al puntero... le dice al compilador que es un puntero.

    puntero = &variable;
    //Si desde un puntero voy a referenciar a una variable short entonces el puntero debe ser short.

    // Vamos a imprimir el contenido de variable y la direccion de memoria
    printf("Variable es igual a %hd y esta en la direccion de memoria %p \n", variable, &variable);
    // Notar que la direccion de memoria se obtiene agregando &

    // Ahora vamos a imprimir el valor donde apunta al puntero y la dire donde apunta ese valor.
    printf("Variable es igual a %hd y esta en %p por referencia \n", *puntero, puntero);

    // Entonces, cual es la direccion del puntero?
    printf("Entonces, %p es la direccion de mi puntero \n", &puntero);

    // Veamos que pasa si asigno mal la variable = quitar el ampersan de puntero = &variable;
}

