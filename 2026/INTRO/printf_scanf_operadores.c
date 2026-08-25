#include <stdio.h>

int main() {
	float precio_unitario, subtotal, total_iva, total_final;
	// float 4 bytes: 0.00000000000000000000000000000000000001175 a 340.282.346.638.528.860.000.000.000.000.000.000.000 (340 quintillones)
	short cantidad;
	// short -32.768 a 32.767
	
	printf("=====================================\n");
	printf("      SISTEMA DE FACTURACION         \n");
	printf("=====================================\n");
	
	printf("Ingrese el precio unitario del producto 1: $");
	scanf("%f", &precio_unitario);
	
	printf("Ingrese la cantidad comprada: ");
	scanf("%hd", &cantidad);
	
	// Cálculos con operadores de asignación y multiplicación
	subtotal = precio_unitario * cantidad;
	total_iva = subtotal * 1.21; // Agrega el 21% de IVA
	
	// Operador de comparación: Devuelve 1 si supera los 10000, 0 si no.
	int aplica_descuento = total_iva > 10000;
	
	// Si aplica_descuento es 1, descuenta el 10%; si es 0, resta 0.
	total_final = total_iva - (total_iva * 0.10 * aplica_descuento);
	
	printf("\n=====================================\n");
	printf("           TICKET DE COMPRA          \n");
	printf("=====================================\n");
	printf("Subtotal (sin IVA)   : $%.2f\n", subtotal);
	printf("Total con IVA (21%%)  : $%.2f\n", total_iva);
	printf("Aplica Descuento 10%% : %c\n", aplica_descuento ? 'S' : 'N');
	printf("-------------------------------------\n");
	printf("TOTAL A PAGAR        : $%.2f\n", total_final);
	printf("=====================================\n");
	
	return 0;
}
