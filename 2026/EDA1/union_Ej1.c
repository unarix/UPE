/*
Union — UNA sola caja, varios usos
	Imaginá esto:
	Tenés una sola caja , pero la usás para guardar distintas cosas en distintos momentos:
	a la mañana → guardás un sandwich
	a la tarde → guardás herramientas
	a la noche → guardás ropa
	La caja es la misma, no crece, no cambia de tamaño
	Solo cambia lo que hay adentro
Lo importante:
	Todos los campos comparten la misma memoria
	Entonces:
	cuando escribís en uno… pisás el anterior
	Resultado: los valores anteriores se pierden
Tamaño de la union
	Es igual al campo más grande
	
*/
	
#include <stdio.h>

// Cuanto puede almacenar esta union?
union Dato {
	int entero; // 4 bytes
	float decimal; // 1 byte
};

int main() {
	union Dato d;
	
	d.entero = 10;
	printf("Entero: %d\n", d.entero);
	
	d.decimal = 3.14;
	printf("Decimal: %f\n", d.decimal);
	
	printf("Entero ahora vale: %d\n", d.entero);
	
	return 0;
}
