#include <stdio.h>

struct Procesador {
    short id_core;
    short temp_celsius;
    short mhz;
    short uso_ventilador;
};

int main(void) {
    /* Inicializamos con valores base; la temperatura se pedira al usuario */
    struct Procesador cpu = {0, 0, 4200, 50};

    printf("Ingrese la temperatura actual de la CPU (en °C): ");
    scanf("%hd", &cpu.temp_celsius);

    printf("\n--- ESTADO INICIAL ---\n");
    printf("Core #%hd: %hd°C a %hd MHz | Ventilador: %hd%%\n\n", 
           cpu.id_core, cpu.temp_celsius, cpu.mhz, cpu.uso_ventilador);

    /* Proteccion termica por hardware */
    if (cpu.temp_celsius > 80) {
        cpu.mhz = 1500;
        cpu.uso_ventilador = 100;

        printf("¡ALERTA DE CALOR!\n");
        printf("Frecuencia reducida a %hd MHz | Ventilador al %hd%%\n", 
               cpu.mhz, cpu.uso_ventilador);
    } else {
        printf("Estado normal. El sistema opera dentro de los parametros seguros.\n");
    }

    return 0;
}
