#include <stdio.h>

union Dato {
	int entero;
	float decimal;
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
