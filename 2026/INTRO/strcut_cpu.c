#include <stdio.h>

struct Procesador {
	short id_core;
	short temp_celsius;
	short mhz;
	short uso_ventilador;
};

int main(void) {
	/* Declaracion ANSI C con tipos short */
	struct Procesador cpu = {0, 85, 4200, 50};
	
	printf("Core #%hd: %hd Grados C a %hd MHz | Ventilador: %hd%%\n", 
		   cpu.id_core, cpu.temp_celsius, cpu.mhz, cpu.uso_ventilador);
	
	/* Proteccion termica por hardware */
	if (cpu.temp_celsius > 80) {
		cpu.mhz = 1500;
		cpu.uso_ventilador = 100;
		
		printf("¡Alerta de calor! Frecuencia reducida a %hd MHz | Ventilador: %hd%%\n", 
			   cpu.mhz, cpu.uso_ventilador);
	}
	
	return 0;
}
