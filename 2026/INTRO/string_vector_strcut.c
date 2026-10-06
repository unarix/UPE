/*

Crear un programa en ANSI C para calcular el tiempo que toma maratonear una serie.
Se registrará en una única estructura:
- Título de la serie (string).
- Duración en minutos de 3 episodios (vector de enteros).

El programa leerá los datos por teclado, sumará el tiempo total y mostrará el resumen en pantalla.
*/
#include <stdio.h>

#define CANT_EPISODIOS 3

/* Definición de la estructura */
struct Serie {
    char titulo[30];                     /* STRING: Título de la serie */
    int minutosEpisodios[CANT_EPISODIOS];/* VECTOR: Duración de cada capítulo */
    int tiempoTotal;
};

int main(void) {
    /* Declaración de variables al inicio (Regla ANSI C / C89) */
    struct Serie miSerie;               /* Una sola variable struct */
    int j;

    /* 1. CARGA DE DATOS */
    printf("=== MARATON DE STREAMING ===\n\n");

    printf("Ingrese el titulo de la serie (sin espacios): ");
    scanf("%s", miSerie.titulo);

    miSerie.tiempoTotal = 0;
    printf("\nIngrese la duracion (en minutos) de los %d episodios:\n", CANT_EPISODIOS);

    for (j = 0; j < CANT_EPISODIOS; j++) {
        printf("  Episodio %d: ", j + 1);
        scanf("%d", &miSerie.minutosEpisodios[j]);
        
        /* Acumulación directa en el campo tiempoTotal */
        miSerie.tiempoTotal += miSerie.minutosEpisodios[j];
    }

    /* 2. RESUMEN FINAL */
    printf("\n===========================================\n");
    printf("           RESUMEN DEL MARATON             \n");
    printf("===========================================\n");
    printf("Serie       : %s\n", miSerie.titulo);
    printf("Episodios   : [%d min, %d min, %d min]\n", 
           miSerie.minutosEpisodios[0], 
           miSerie.minutosEpisodios[1], 
           miSerie.minutosEpisodios[2]);
    printf("Tiempo Total: %d minutos (~%.1f horas)\n", 
           miSerie.tiempoTotal, 
           miSerie.tiempoTotal / 60.0);
    printf("===========================================\n");

    return 0;
}
