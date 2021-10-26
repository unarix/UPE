
// Bueno, veamos mediante un ejemplo muy simple para que puedo yo usar extructuras con funciones. 
// Generalmente usamos esto para que una funcion nos retorne mas de un solo dato, pero no siempre es asi
// y no siempre se usa este metodo, tambien se pueden usar punteros que veremos mas adelante. 
// Hoy vemos esto como una solucion para retornar mas de un valor con lo que sabemos. 

// Supongamos que nos piden que ingresemos dos numeros cualquiera, y que en una unica funcion hagamos su 
// Multiplicacion, divicion, resta y suma
// Todo dentro de la misma funcion e imprimamos al finalizar los resultados

#include <stdio.h>

struct operaciones{
    short multipl;
    short division;
    short suma;
    short resta;
};

struct operaciones resolverOper(short a, short b);

int main(void)
{
    short a,b;
    
    printf("Ingrese el num 1: ");
    scanf("%hd",&a);
    
    printf("Ingrese el num 2: ");
    scanf("%hd",&b);

    // Legar hasta aca y hacer la funcion... 
    
    struct operaciones result = resolverOper(a,b);

    printf("\n *** Resultados *** \n");
    printf(" - Multiplicacion: %hd\n",result.multipl);
    printf(" - Division: %hd\n",result.division);
    printf(" - Suma: %hd\n",result.suma);
    printf(" - Resta: %hd\n",result.resta);

    return 0;
}


struct operaciones resolverOper(short a, short b) //Que me falta para que el compilador sepa que existo? 
{
    struct operaciones resultados;

    resultados.multipl = a*b;
    resultados.division = a/b;
    resultados.suma = a+b;
    resultados.resta = a-b;

    return resultados;
}
