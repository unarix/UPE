#include <stdio.h>

/*
Implementar un monitoreo en loop continuo para un procesador que aplique proteccion termica a mas de 80 grados.
*/

struct Procesador {
	short id_core;
	short temp_celsius;
	short mhz;
	short uso_ventilador;
};

int main(void) {
	/* Estado base del procesador */
	struct Procesador cpu = {0, 0, 4200, 50};
	
	/* Bucle infinito de monitoreo */
	while (1) {
		printf("\n----------------------------------------\n");
		printf("Ingrese la temperatura de la CPU en grados C (Ctrl+C para salir): ");
		scanf("%hd", &cpu.temp_celsius);
		
		/* Evaluacion del estado y reaccion automatica */
		if (cpu.temp_celsius > 80) {
			cpu.mhz = 1500;
			cpu.uso_ventilador = 100;
			
			printf("ALERTA TERMICA!\n");
			printf("Core #%hd: %hdC | Frecuencia: %hd MHz | Ventilador: %hd%%\n", 
				   cpu.id_core, cpu.temp_celsius, cpu.mhz, cpu.uso_ventilador);
		} else {
			/* Se restauran los valores normales si la temperatura baje de 80°C */
			cpu.mhz = 4200;
			cpu.uso_ventilador = 50;
			
			printf("Estado Normal.\n");
			printf("Core #%hd: %hdC | Frecuencia: %hd MHz | Ventilador: %hd%%\n", 
				   cpu.id_core, cpu.temp_celsius, cpu.mhz, cpu.uso_ventilador);
		}
	}
	
	return 0;
}
