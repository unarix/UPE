/*

Crear un programa en ANSI C para calcular el tiempo que toma maratonear una serie de 3 episorios.
Se registrará en una única estructura:
- Título de la serie (string).
- Duración en minutos de 3 episodios (vector de enteros).
- Calificaciones (1 a 10)

El programa leerá los datos por teclado, 
sumará el tiempo total, calculara la calificacion promedio y mostrará el resumen en pantalla.

*/

#include <stdio.h>

#define CANT_EPISODIOS 3

/* Definición de la estructura */
struct Serie {
	char titulo[30];                         /* STRING: Título de la serie */
	short minutosEpisodios[CANT_EPISODIOS];  /* VECTOR 1: Duración de cada capítulo */
	short calificaciones[CANT_EPISODIOS];    /* VECTOR 2: Estrellas de 1 a 10 */
	short tiempoTotal;
	float promedioCalificacion;
};

int main(void) {
	/* Declaración de variables al inicio (Regla ANSI C / C89) */
	struct Serie miSerie;                    /* Una sola variable struct */
	short i;
	short sumaCalificaciones = 0;
	
	/* 1. CARGA DE DATOS */
	printf("=== MARATON DE STREAMING ===\n\n");
	
	printf("Ingrese el titulo de la serie (sin espacios): ");
	scanf("%s", miSerie.titulo);
	
	miSerie.tiempoTotal = 0;
	printf("\nIngrese los datos de los %d episodios:\n", CANT_EPISODIOS);
	
	for (i = 0; i < CANT_EPISODIOS; i++) {
		printf("\n--- Episodio %hd ---\n", i + 1);
		
		printf("  Duracion (en minutos): ");
		scanf("%hd", &miSerie.minutosEpisodios[i]);
		
		printf("  Calificacion (1 a 10 estrellas): ");
		scanf("%hd", &miSerie.calificaciones[i]);
		
		/* Acumulación directa de tiempos y calificaciones */
		miSerie.tiempoTotal += miSerie.minutosEpisodios[i];
		sumaCalificaciones += miSerie.calificaciones[i];
	}
	
	/* Cálculo del promedio con casteo explícito a float */
	miSerie.promedioCalificacion = (float)sumaCalificaciones / CANT_EPISODIOS;
	
	/* 2. RESUMEN FINAL */
	printf("\n===========================================\n");
	printf("           RESUMEN DEL MARATON             \n");
	printf("===========================================\n");
	printf("Serie         : %s\n", miSerie.titulo);
	printf("Episodios     : [%hd min, %hd min, %hd min]\n", 
		   miSerie.minutosEpisodios[0], 
		   miSerie.minutosEpisodios[1], 
		   miSerie.minutosEpisodios[2]);
	printf("Calificaciones: [%hd/10, %hd/10, %hd/10]\n", 
		   miSerie.calificaciones[0], 
		   miSerie.calificaciones[1], 
		   miSerie.calificaciones[2]);
	printf("-------------------------------------------\n");
	printf("Tiempo Total  : %hd minutos (~%.1f horas)\n", 
		   miSerie.tiempoTotal, 
		   miSerie.tiempoTotal / 60.0);
	printf("Promedio      : %.2f / 10 estrellas\n", miSerie.promedioCalificacion);
	printf("===========================================\n");
	
	return 0;
}
