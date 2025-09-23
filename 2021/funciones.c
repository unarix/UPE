#include <stdio.h>

short sumar(short, short); // PROTOTIPO
void separar_texto(); // PROTOTIPO

int main()
{
    // **** Que es una funcion ***** //
    // Una función es un conjunto de instrucciones.. que se agrupan bajo un nombre y que se puede ejecutar o “llamar”... desde distintas partes del programa.

    // Tambien: Es un sub algoritmo compuesto por un conjunto de intrucciones que permite resolver una tarea especifica y que forma parte del algoritmo principal
    // - Generalmente no sabemos que pasa dentro de la funcion, por eso le decimos: Caja negra
    // - De la funcion, sabemos lo que recibe y lo que retorna, pero no que hace dentro.
    
    // **** Para que o porque las usamos? Ventajas de usar funciones ***** //
    // Disminuir cantidad de codigo y errores porque centralizamos todo en un bloque de codigo.
    // Reducir la complejidad del programa --> porque usando funciones ahorramos cantidad de lineas de codigo
    // No duplicar el codigo
    // Reutilizar el codigo --> puedo hacer mis propias funciones y usarlas en otros programas
    // Facilitar la portabilidad (Ejemplo bibliotecas/librerias)
    
    // Nosotros ya conocemos funciones, las usamos pero vamos a aprender como hacerlas
    // por ejemplo, printf es una funcion.
    printf("Hola mundo\n");

    // **** Las funciones tienen algunas caracteristicas como: **** // 
    
    // Los parametros de una funcion
    // Los parametros son las variables que enviamos a la funcion para que haga su tarea
    // en el ejemplo del printf le enviamos un string para que ese string lo imprima en la pantalla 

    // El retorno de la funcion 
    // Cada función puede devolver un valor con un tipo de dato específico (como int, float, char, etc.). Si no devuelve nada, se declara como void.
    
    // **** Ahora vamos a programar una funcion propria ***** //
    // Hagamos nuestra primer funcion que suma:
    // NO NOS OLVIDEMOS DEL PROTOTIPO!
    printf("La suma da como resultado: %hd \n", sumar(2,3) );
    
    separar_texto();

    // Otra forma de mostrar lo mismo que antes
    short suma = sumar(2,3);
    printf("La suma da como resultado: %hd \n", suma );
    
    // **** El cliclo de vida de las variables ***** //
    // El ámbito junto a todas sus variables dura el tiempo que está activa la función, 
    // Si se vuelve a llamar o invocar se crea un nuevo ámbito y como consecuencia de nuevo sus variables.
    // Las variables se envian por copia... el valor de la variable original (desde fue llamada la funcion) no cambia!

    // **** Hagamos una funcion que me haga un separador ***** //
    // Esta funcion no recibe ni retorna ningun parametro
    separar_texto();

    return 0;
}

// IMPORTANTE: SIEMPRE QUE HAGO UNA FUNCION, DEBO DECLARAR SU PROTOTIPO.
short sumar(short num1, short num2)
{
    short suma = num1 + num2;
    return suma;
    //return num1+num2; //<-- esta es otra forma de retornar mas simple que la anterior
    
    separar_texto(); // <--- cuando llamo a una funcion dentro de otra, le decimos funciones anidadas.
}

void separar_texto()
{
    printf("\n");
    printf("****************************************");
    printf("\n");
}
