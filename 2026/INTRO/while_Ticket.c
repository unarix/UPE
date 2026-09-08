#include <stdio.h>

int main() {
    float precio_unitario, subtotal, total_iva, total_final;
    short cantidad;
    int metodo_pago;
    float porcentaje_descuento = 0.0;
    float recargo = 0.0;

    printf("=====================================\n");
    printf("        SISTEMA DE FACTURACION        \n");
    printf("=====================================\n");

    printf("Ingrese el precio unitario del producto: $");
    scanf("%f", &precio_unitario);

    printf("Ingrese la cantidad comprada: ");
    scanf("%hd", &cantidad);

    // VALIDAR QUE LA CANTIDAD Y EL PRECIO SEAN MAYOR A CERO
    if (precio_unitario <= 0 || cantidad <= 0) {
        printf("\n[ERROR] El precio y la cantidad deben ser mayores a cero.\n");
        return 1; 
    }

    subtotal = precio_unitario * cantidad;
    total_iva = subtotal * 1.21;

    // DETERMINAR DESCUENTO SEGÚN EL MONTO
    if (total_iva >= 20000) {
        porcentaje_descuento = 0.15; 
    } else if (total_iva >= 10000) {
        porcentaje_descuento = 0.10; 
    } else if (total_iva >= 5000) {
        porcentaje_descuento = 0.05; 
    } else {
        porcentaje_descuento = 0.0;  
    }

    // ------------------------------------------------------------------
    // BUCLE WHILE: Validación interactiva del método de pago
    // ------------------------------------------------------------------
    printf("\nSeleccione el metodo de pago (1: Efectivo, 2: Tarjeta): ");
    scanf("%d", &metodo_pago);

    // MIENTRAS el método sea distinto de 1 Y distinto de 2, vuelve a pedirlo
    while (metodo_pago != 1 && metodo_pago != 2) {
        printf("[ERROR] Opción no válida. Por favor ingrese 1 (Efectivo) o 2 (Tarjeta): ");
        scanf("%d", &metodo_pago);
    }

    // Una vez superado el while, sabemos con certeza que metodo_pago es 1 o 2
    if (metodo_pago == 1) {
        if (total_iva >= 10000) {
            porcentaje_descuento += 0.02; // Bonificación extra por pago en efectivo
        }
    } else { // Equivale a metodo_pago == 2
        recargo = total_iva * 0.05; // Recargo por tarjeta
    }

    // Cálculos finales
    float monto_descuento = total_iva * porcentaje_descuento;
    total_final = (total_iva - monto_descuento) + recargo;

    printf("\n=====================================\n");
    printf("            TICKET DE COMPRA          \n");
    printf("=====================================\n");
    printf("Subtotal (sin IVA)   : $%.2f\n", subtotal);
    printf("Total con IVA (21%%)  : $%.2f\n", total_iva);
    printf("Descuento aplicado   : %.0f%%\n", porcentaje_descuento * 100);

    if (recargo > 0) {
        printf("Recargo por Tarjeta  : $%.2f\n", recargo);
    }

    printf("Envio a domicilio    : %s\n", (total_final > 15000) ? "GRATIS" : "$500.00");
    printf("-------------------------------------\n");
    printf("TOTAL A PAGAR        : $%.2f\n", total_final);
    printf("=====================================\n");

    return 0;
}
