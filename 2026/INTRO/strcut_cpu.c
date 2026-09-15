#include <stdio.h>

struct Procesador {
    int id_core;
    int temp_celsius;
    int mhz;
};

int main(void) {
    /* Declaracion ANSI C */
    struct Procesador cpu = {0, 85, 4200};

    printf("Core #%d: %d°C a %d MHz\n", cpu.id_core, cpu.temp_celsius, cpu.mhz);

    /* Proteccion termica por hardware */
    if (cpu.temp_celsius > 80) {
        cpu.mhz = 1500;
        printf("¡Alerta de calor! Frecuencia reducida a %d MHz\n", cpu.mhz);
    }

    return 0;
}
