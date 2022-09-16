// Hacemos algo bien facil y repasamos funciones, estructuras y demas? 
// algo que siempre fallan es en algun calculo, asique vemos como sacar un porcentaje por ejemplo? 
// hagamoslo bien corto y que surjan dudas
// en estos temas no podemos fallar en el examen

// Nos piden hacer un programar que: 
// le tenemos que pasar dos parametros y me tiene que retornar tres resultados
// en los calculos tengo que hacer porcentajes... dos deben estar mal calculados y uno debe estar bien
// Los datos que se pasan a la funcion por parametro son inventados y de cualquier tipo que quieran

#include <stdio.h> // esto como se llama? y que tienen adentro para que sirven? 
#include <string.h>

struct calculos{
    float porcentaje_uno;s
	float porcentaje_dos;
	float porcentaje_tres;
};

struct calculos calcularPorcentajes(float poblacion,float total); //Prototipo!! 

int main() { // main es una funcion?

	struct calculos porcentajes;

	porcentajes = calcularPorcentajes(2,1000);

	printf("\n");

	printf("porc1 es: %.2f%\n", porcentajes.porcentaje_uno);
	printf("porc2 es: %.2f%\n", porcentajes.porcentaje_dos);
	printf("porc3 es: %.2f%\n", porcentajes.porcentaje_tres);

	printf("\n - Cual es el correcto?? \n\n");

	return 0; // que tipo de dato tiene que ser el que retorna? 
}

struct calculos calcularPorcentajes(float cantidad,float capacidad) //porque uso funciones? que ventaja tiene eso? 
{
	struct calculos porcentajes;
	porcentajes.porcentaje_uno = cantidad*100/capacidad;
	porcentajes.porcentaje_dos = cantidad*capacidad/100;
	porcentajes.porcentaje_tres = capacidad*100/cantidad;
	return porcentajes;
}
