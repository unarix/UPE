#include <stdio.h>
#include <string.h>

#define N 4
#define MAX_NOMBRE 50

float calcularPromedioEdad(short suma, short n); //Prototipo

// Definición de la estructura
struct persona{
    short legajo;
    char nombre[MAX_NOMBRE];
    short edad;
};

int main() {
    struct persona personas[N];
    short i;
    short edadMax, edadMin, suma = 0, opcion;

    // Cargar datos
    for (i = 0; i < N; i++) {
        printf("Persona %hd:\n", i + 1);
        printf("Legajo: ");
        scanf("%hd", &personas[i].legajo);
        printf("Nombre: ");
        scanf(" %s", personas[i].nombre);
        printf("Edad: ");
        scanf("%hd", &personas[i].edad);

        // La utilizo para el calculo del promedio.
        suma += personas[i].edad;
    }
    printf("\n suma: %hd\n",suma);

    printf("========= MENU =========\n");
    printf("1. Ordenar por edad (ascendente)\n");
    printf("2. Ordenar por legajo y luego edad (ascendente)\n");
    printf("========================\n");
    printf("Ingrese una opcion: ");
    scanf("%hd", &opcion);


    // Ordenar a las personas por el metodo de burbuja
    struct persona temp;
    short ordenado;
    
    short R = 0;
    switch (opcion) {
            case 1:
                R = 0;
                // Ordenar con burbuja (Double Sort) // solo por edad!
                do{
                    ordenado = 0;
                    R++;
                    for (short i = 0; i < N-R; i++) {
                        if (personas[i].edad > personas[i + 1].edad) {
                            temp = personas[i];
                            personas[i] = personas[i + 1];
                            personas[i + 1] = temp;
                            ordenado = 1;
                        }
                    }
                }while (ordenado);
                break;
            case 2:
                // Ordenar con burbuja (Double Sort) // por legajo y luego por edad!
                R = 0;
                do{
                    ordenado = 0;
                    R++;
                    for (short i = 0; i < N-R; i++) {
                        short cambiar = 0;
                        if (personas[i].legajo > personas[i + 1].legajo) {
                            cambiar = 1;
                        }
                        // Segundo criterio: si las edades son iguales, ordenar por promedio (descendente)
                        else if (personas[i].legajo == personas[i + 1].legajo &&
                                 personas[i].edad > personas[i + 1].edad) {
                            cambiar = 1;
                        }

                        if (cambiar == 1) {
                            temp = personas[i];
                            personas[i] = personas[i + 1];
                            personas[i + 1] = temp;
                            ordenado = 1;
                        }
                    }
                }while (ordenado);
                break;
    }

    /*
    // Ordenar a las personas por el metodo de pivot
    struct informacion temp;
    for (short i = 0; i < n - 1; i++) {
        for (short j = i + 1; j < n; j++) {
            if (persona[i].edad > persona[j].edad) {
                temp = persona[i];
                persona[i] = persona[j];
                persona[j] = temp;
            }
        }
    }
    */

    // Mostrar todos los datos
    printf("\n--- Listado de personas ---\n");
    for (i = 0; i < N; i++) {
        printf("Legajo: %d | Nombre: %s | Edad: %d\n",
               personas[i].legajo,
               personas[i].nombre,
               personas[i].edad);
    }

    // Mostrar persona de edad maxima y edad minima.
    // Buscar edad máxima y mínima
    edadMax = edadMin = personas[0].edad;
    for (i = 1; i < N; i++) {
        if (personas[i].edad > edadMax) edadMax = personas[i].edad;
        if (personas[i].edad < edadMin) edadMin = personas[i].edad;
    }
    printf("\n--- Personas con edad maxima (%hd anios) ---\n", edadMax);
    for (i = 0; i < N; i++) {
        if (personas[i].edad == edadMax) {
            printf("Nombre: %s | Legajo: %d\n", personas[i].nombre, personas[i].legajo);
        }
    }
    printf("\n--- Personas con edad minima (%hd anios) ---\n", edadMin);
    for (i = 0; i < N; i++) {
        if (personas[i].edad == edadMin) {
            printf("Nombre: %s | Legajo: %hd\n", personas[i].nombre, personas[i].legajo);
        }
    }

    // Calcular y mostrar promedio de edad
    float promedio = calcularPromedioEdad(suma, N);
    printf("\nPromedio de edad: %.2f\n", promedio);

    // Búsqueda por legajo o nombre
    short legajo;
    char nombreBuscado[MAX_NOMBRE];
    printf("\nBuscar por (1) Legajo o (2) Nombre: ");
    scanf("%hd", &opcion);

    short encontrado = 0;

    if (opcion == 1) {
        printf("Ingrese legajo: ");
        scanf("%hd", &legajo);
        for (i = 0; i < N; i++) {
            if (personas[i].legajo == legajo) {
                printf("Legajo: %hd | Nombre: %s | Edad: %hd\n",
                       personas[i].legajo,
                       personas[i].nombre,
                       personas[i].edad);
                encontrado = 1;
            }
        }
    } else if (opcion == 2) {
        printf("Ingrese nombre: ");
        scanf(" %s", nombreBuscado);

        for (i = 0; i < N; i++) {
            if (strcmp(personas[i].nombre, nombreBuscado) == 0) {
                printf("Legajo: %d | Nombre: %s | Edad: %d\n",
                       personas[i].legajo,
                       personas[i].nombre,
                       personas[i].edad);
                encontrado = 1;
            }
        }
    } else {
        printf("Opción inválida.\n");
    }

    if (!encontrado) {
        printf("Persona no encontrada.\n");
    }

    return 0;
}

// Calcular promedio de edad
float calcularPromedioEdad(short suma, short n) {
    return (float)suma / n;
}
