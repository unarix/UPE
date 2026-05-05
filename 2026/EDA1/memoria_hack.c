// Cuidado con Realloc... puede mover todo el contenido a otra parte de la memoria si ya no tiene lugar para reallocar donde vivia previamente. 
// Evitar punteros que apunten a vectores cuando usamos memoria dinamica!

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char buffer[8];
	int autenticado = 0;
		
	if (argc < 2) {
		printf("Uso: %s <password>\n", argv[0]);
		return 1;
	}
	
	strcpy(buffer, argv[1]); // Copia el valor del argumento enviado en buffer. El problema? desborda el buffer.
	
	if (strcmp(buffer, "admin") == 0) { // con el buffer desbordado aca no entra, pero autenticado es cualquier cosa que no sea 0
		autenticado = 1;
	}
	
	if (autenticado) { // como autenticado tiene basura del desborde no es 0, si no es 0 entonces es verdadero.
		printf("Acceso permitido\n");
	} else {
		printf("Acceso denegado\n");
	}
	
	return 0;
}
