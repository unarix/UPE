// Cuando escribís un programa en C (u otros lenguajes), necesitás guardar datos en memoria mientras el programa se ejecuta. Eso puede hacerse de dos formas:

// 1. Memoria estática
//		Es la que usás cuando declarás variables normales, como:
// 		int numero = 5;
// 		El tamaño y la duración de esa memoria ya están definidos en tiempo de compilación.
// 		El problema: no podés cambiar el tamaño mientras el programa corre.

// 2. Memoria dinámica
//		Es memoria que pedís "a demanda" durante la ejecución del programa.

// Usás funciones como malloc, calloc, o realloc para reservarla.

// Cuando ya no la necesitás, la liberás con free().

// ¿Por qué usar memoria dinámica?
// 		Porque a veces no sabés cuántos datos vas a tener hasta que el programa esté corriendo.

// ¿Dónde se guarda?
// 		La memoria dinámica se guarda en un lugar especial llamado heap. Es diferente del stack, que es donde van las variables normales (como int a = 5;).
// 		Si no liberás la memoria con free(), se queda reservada en el heap aunque ya no la uses. 
//		Esto se llama fuga de memoria (memory leak), y puede hacer que tu programa consuma más y más memoria hasta fallar.

// Función	Qué hace
// malloc	Reserva memoria (no la inicializa)
// calloc	Reserva memoria e inicializa en 0
// realloc	Cambia el tamaño de un bloque existente
// free		Libera la memoria que ya no usás

#include <stdio.h>
#include <stdlib.h>

int main()
{

    short *puntero_a_entero;

    printf("\nCrearemos un espacio para almacenar un entero \n");
    printf("y lo haremos en TIEMPO DE EJECUCION \n\n");

    puntero_a_entero=(short *)malloc(sizeof(short));

    printf("Ahora le damos un valor desde teclado: ");
    scanf("%hd",puntero_a_entero);

    printf("\nlo ingresado fue: %hd\n\n",  *puntero_a_entero);

    printf("...y ahora lo eliminamos de memoria\n");
    printf("lo haremos haciendo free(puntero_a_entero)\n");
    puntero_a_entero=NULL;
    
    free((short *)puntero_a_entero);
    
    if(puntero_a_entero!=NULL)
        printf("\nlo ingresado fue: %hd\n\n",*puntero_a_entero);
    else
        printf("el puntero no existe!!\n\n");

    return 0;
}






#include <stdio.h>
#include <stdlib.h>

// Crear un programa que me permita generar un vector dinamico solicitandole al usuario la cantidad de posiciones que va a tener. 
// Luego llenar esas posiciones con numeros contiguos para finalmente imprimirlos en una nueva linea

int main()
{
  
    // Este puntero va a almacenar la direc inicial del bloque creado
    short *ptr;
    short i;
    short numero;
  
    // Obtener el numero de elementos
    printf("Ingresar un numero de elementos:\n");
    scanf("%hd",&numero);

    // alocacion de memoria para el vector dinamicamente usando malloc
    ptr = (short*)malloc(numero * sizeof(short));
  
    // Check si la memoria fue alocada satisfactoriamente o no
    if (ptr == NULL) {
        printf("Memoria no alocada correctamente por falta de espacio.\n");
        exit(0);
    }
    else {
        // La memoria fue reservada correctamente
        printf("Memoria alocada correctamente.\n");
  
        // llenar los elementos del array
        for (i = 0; i < numero; ++i) {
            ptr[i] = i + 1;
        }
  
        // Imprimir los elementos del array
        printf("Los elementos del array son: ");
        for (i = 0; i < numero; ++i) {
            printf("%d, ", ptr[i]);
        }
        printf("\n");
    }
  
    return 0;
}

// Crear un programa que me permita generar un vector dinamico solicitandole al usuario la cantidad de posiciones que va a tener. 
// una vez ingresados los numeros sumarlos a todos y volver a solicitar mas numeros usando el mismo vector.

#include <stdio.h>
#include <stdlib.h>

int main() {
    short *numeros;
    short cantidad, nueva_cantidad;
    short suma = 0;

    printf("¿Cuántos números querés ingresar? ");
    scanf("%d", &cantidad);

    // Usamos calloc para inicializar en 0
    numeros = (short*) calloc(cantidad, sizeof(short));

    if (numeros == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Ingresar valores
    printf("Ingresá %d números:\n", cantidad);
    for (short i = 0; i < cantidad; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &numeros[i]);
        suma += numeros[i];
    }

    printf("Suma total: %d\n", suma);

    // Supongamos que queremos agregar más números
    printf("¿Cuántos números más querés agregar? ");
    scanf("%d", &nueva_cantidad);

    // Aumentamos el tamaño del arreglo con realloc
    numeros = (short*) realloc(numeros, (cantidad + nueva_cantidad) * sizeof(short));

    if (numeros == NULL) {
        printf("Error al reasignar memoria.\n");
        return 1;
    }

    // Ingresar los nuevos valores
    printf("Ingresá los %d nuevos números:\n", nueva_cantidad);
    for (short i = cantidad; i < cantidad + nueva_cantidad; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &numeros[i]);
        suma += numeros[i];
    }

    printf("Nueva suma total: %d\n", suma);

    // Liberamos la memoria
    free(numeros);
    numeros = NULL;  // Buena práctica

    return 0;
}