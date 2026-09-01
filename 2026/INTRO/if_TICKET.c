#include <stdio.h>

int main() {
    float precio_unitario, subtotal, total_iva, total_final;
    short cantidad;
    int metodo_pago;
    float porcentaje_descuento = 0.0;
    float recargo = 0.0;

    printf("=====================================\n");
    printf("       SISTEMA DE FACTURACION        \n");
    printf("=====================================\n");

    printf("Ingrese el precio unitario del producto: $");
    scanf("%f", &precio_unitario);

    printf("Ingrese la cantidad comprada: ");
    scanf("%hd", &cantidad);

    // VALIDAR QUE LA CANTIDAD Y EL PRECIO SEAN MAYOR A CERO!
    // 1. IF SIMPLE (Validacion de entrada / Cláusula de guarda)
    if (precio_unitario <= 0 || cantidad <= 0) {
        printf("\n[ERROR] El precio y la cantidad deben ser mayores a cero.\n");
        return 1; // Aborta la ejecución del programa
    }

    subtotal = precio_unitario * cantidad;
    total_iva = subtotal * 1.21;

    // SI EL TOTAL CON IVA SUPERA LOS 20MIL APLICAR DESPUENTO DEL 15%!
    // SI EL TOTAL CON IVA SUPERA LOS 10MIL APLICAR DESPUENTO DEL 10%!
    // SI EL TOTAL CON IVA SUPERA LOS 5MIL APLICAR DESPUENTO DEL 5%!
    // SI NO, no aplicar descuento.!
    // 2. IF - ELSE IF - ELSE (Estructura de cascada por rangos)

    /* 
    Operador,    Significado,    Ejemplo,        Condición (suponiendo x = 5)
    ==,          Igual a,if (x == 5),            Verdadero
    !=,          Distinto de,if (x != 5),        Falso
    >,           Mayor que,if (x > 3),           Verdadero
    <,           Menor que,if (x < 10),          Verdadero
    >=,          Mayor o igual que,if (x >= 5),  Verdadero
    <=,          Menor o igual que,if (x <= 4),  Falso
    */
    
    if (total_iva >= 20000) {
        porcentaje_descuento = 0.15; // 15% de descuento
    } else if (total_iva >= 10000) {
        porcentaje_descuento = 0.10; // 10% de descuento
    } else if (total_iva >= 5000) {
        porcentaje_descuento = 0.05; // 5% de descuento
    } else {
        porcentaje_descuento = 0.0;  // Sin descuento
    }

    // 3. IF - ELSE con IF ANIDADO (Forma de pago)
    // QUE PERMITA SELECCIONAR EL METODO DE PAGO: 1 EFECTIVO / 2 TARJETA
    // SI EL PAGO ES EN EFECTIVO APLICA UN 2% DE DESCUENTO EXTRA PERO SOLO SI EL MONTO ES MAYOR A DIEZMIL
    // SI ES CON TARJETA UN 5% DE RECARGO.
    // SI PUSO UNA OPCION INVALIDA INFORMARLO.
    printf("\nSeleccione el metodo de pago (1: Efectivo, 2: Tarjeta): ");
    scanf("%d", &metodo_pago);

    if (metodo_pago == 1) {
        // IF ANIDADO: Solo en efectivo aplica un 2% extra si supera los $10.000
        if (total_iva >= 10000) {
            porcentaje_descuento += 0.02; // Bonificación extra
        }
    } else if (metodo_pago == 2) {
        recargo = total_iva * 0.05; // 5% de recargo por tarjeta
    } else {
        printf("\n[AVISO] Metodo no valido. Se procesara como Efectivo sin bonificacion.\n");
    }

    // Cálculos finales
    float monto_descuento = total_iva * porcentaje_descuento;
    total_final = (total_iva - monto_descuento) + recargo;

    printf("\n=====================================\n");
    printf("           TICKET DE COMPRA          \n");
    printf("=====================================\n");
    printf("Subtotal (sin IVA)   : $%.2f\n", subtotal);
    printf("Total con IVA (21%%)  : $%.2f\n", total_iva);
    printf("Descuento aplicado   : %.0f%%\n", porcentaje_descuento * 100);

    // 4. IF SIMPLE PARA SALIDA DE DATOS
    if (recargo > 0) {
        printf("Recargo por Tarjeta  : $%.2f\n", recargo);
    }

    // 5. OPERADOR TERNARIO (Alternativa corta de IF/ELSE)
    printf("Envio a domicilio    : %s\n", (total_final > 15000) ? "GRATIS" : "$500.00");

    printf("-------------------------------------\n");
    printf("TOTAL A PAGAR        : $%.2f\n", total_final);
    printf("=====================================\n");

    return 0;
}
