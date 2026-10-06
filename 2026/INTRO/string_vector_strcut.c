#include <stdio.h>

#define CANT_SERIES 2
#define CANT_EPISODIOS 3

/* Definición de la estructura */
struct Serie {
    char titulo[30];                     /* String */
    int minutosEpisodios[CANT_EPISODIOS];/* Vector dentro de la estructura */
    int tiempoTotal;
};

int main(void) {
    /* Declaración de variables al inicio (Regla ANSI C / C89) */
    struct Serie maraton[CANT_SERIES];   /* Vector de estructuras */
    int i, j;

    /* 1. CARGA DE DATOS Y CÁLCULO */
    for (i = 0; i < CANT_SERIES; i++) {
        printf("--- Registro de Serie %d ---\n", i + 1);
        
        printf("Titulo de la serie (sin espacios): ");
        scanf("%s", maraton[i].titulo);

        maraton[i].tiempoTotal = 0;
        printf("Ingrese la duracion (minutos) de los %d episodios:\n", CANT_EPISODIOS);
        
        for (j = 0; j < CANT_EPISODIOS; j++) {
            printf("  Episodio %d: ", j + 1);
            scanf("%d", &maraton[i].minutosEpisodios[j]);
            maraton[i].tiempoTotal += maraton[i].minutosEpisodios[j];
        }
        printf("\n");
    }

    /* 2. RESUMEN FINAL DE STREAMING */
    printf("===========================================\n");
    printf("        RESUMEN DEL MARATON STREAMING      \n");
    printf("===========================================\n");
    
    for (i = 0; i < CANT_SERIES; i++) {
        printf("Serie       : %s\n", maraton[i].titulo);
        printf("Episodios   : [%d min, %d min, %d min]\n", 
               maraton[i].minutosEpisodios[0], 
               maraton[i].minutosEpisodios[1], 
               maraton[i].minutosEpisodios[2]);
        printf("Tiempo Total: %d minutos (~%.1f horas)\n", 
               maraton[i].tiempoTotal, 
               maraton[i].tiempoTotal / 60.0);
        printf("-------------------------------------------\n");
    }

    return 0;
}
