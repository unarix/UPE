#include <stdio.h>

/* 1. Definicion del struct */
struct Estudiante {
    char curso;
    short edad;
    float promedio;
    short legajo;
};

int main(void) {
    /* 2. Declaracion e inicializacion (ANSI C exige declarar variables al inicio del bloque) */
    struct Estudiante alumno1 = {"A", 21, 9.5, 4439};
    alumno1.legajo = 5050;
  
    /* 3. Acceso a los campos con el operador punto (.) */
    printf("--- Datos del Estudiante ---\n");
    printf("Nombre: %s\n", alumno1.nombre);
    printf("Edad: %d anos\n", alumno1.edad);
    printf("Promedio: %.1f\n", alumno1.promedio);
    printf("Legajo: %.1f\n", alumno1.legajo);

    return 0;
}
