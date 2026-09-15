#include <stdio.h>

/* 
	Un struct  es un tipo de dato! personalizado que permite agrupar 
	variables de diferentes tipos (enteros, texto, flotantes, etc.) 
	En ANSI C se define técnicamente como un tipo de dato compuesto 
	En lenguajes O.O es la representacion de una entidad.
*/

/* 1. Definicion del struct */
struct Estudiante {
	char curso;
	short edad;
	float promedio;
	short legajo;
};

int main(void) {
	/* 2. Declaracion e inicializacion (ANSI C exige declarar variables al inicio del bloque) */
	struct Estudiante alumno1 = {'A', 21, 9.5, 4439};
	//alumno1.legajo = 5050;
	
	/* 3. Acceso a los campos con el operador punto (.) */
	printf("--- Datos del Estudiante ---\n");
	printf("Nombre: %c\n", alumno1.curso);
	printf("Edad: %hd anios\n", alumno1.edad);
	printf("Promedio: %.1f\n", alumno1.promedio);
	printf("Legajo: %.hd\n", alumno1.legajo);
	
	return 0;
}
