/*
Campos de bits — usar memoria como si fuera un TETRIS
  Vida real:
    Imaginá un panel de luces:
      Encendido → 1
      Apagado → 0
    Tenés 8 luces → podrías usar 8 variables…
      desperdicio total
    Mejor usar 1 byte (8 bits) y controlar cada luz individualmente

union
  = una sola memoria, varios significados (pero uno a la vez)
campos de bits
  = dividir la memoria al máximo (bit por bit)

*/
#include <stdio.h>

union Panel {
	struct {
		unsigned l1:1;
		unsigned l2:1;
		unsigned l3:1;
		unsigned l4:1;
		unsigned l5:1;
		unsigned l6:1;
		unsigned l7:1;
		unsigned l8:1;
	} luces;
	unsigned char valor;
};

// Mostrar en formato de luces
void mostrarLuces(union Panel p) {
	printf("Luces: %d %d %d %d %d %d %d %d\n",
		   p.luces.l8, p.luces.l7, p.luces.l6, p.luces.l5,
		   p.luces.l4, p.luces.l3, p.luces.l2, p.luces.l1);
}

// Mostrar valor entero
void mostrarValor(union Panel p) {
	printf("Valor entero: %d\n", p.valor);
}

int main() {
	union Panel panel;
	
	// Inicializar todo apagado
	panel.valor = 0;
	mostrarLuces(panel);
	mostrarValor(panel);
	
	// Encender luz 2 usando número
	panel.valor = 2; // 00000010
	mostrarLuces(panel);
	mostrarValor(panel);
	
	// Encender luz 1 manualmente
	panel.luces.l1 = 1;
	mostrarLuces(panel);
	mostrarValor(panel);
	
	// Encender luz 8
	panel.valor = 255;
	mostrarLuces(panel);
	mostrarValor(panel);
	
	return 0;
}
