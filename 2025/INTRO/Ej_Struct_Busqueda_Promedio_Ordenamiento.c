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
    short edadMax, edadMin, suma = 0;

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

    // Ordenar a las personas por el metodo de burbuja
    struct persona temp;
    for (short i = 0; i < N - 1; i++) {
        for (short j = 0; j < N - 1 - i; j++) {
            if (personas[j].edad > personas[j + 1].edad) {
                temp = personas[j];
                personas[j] = personas[j + 1];
                personas[j + 1] = temp;
            }
        }
    }

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
    short opcion, legajo;
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
