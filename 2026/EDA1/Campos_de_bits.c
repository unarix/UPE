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

struct Luces {
    unsigned int l1 : 1;
    unsigned int l2 : 1;
    unsigned int l3 : 1;
    unsigned int l4 : 1;
    unsigned int l5 : 1;
    unsigned int l6 : 1;
    unsigned int l7 : 1;
    unsigned int l8 : 1;
};

// Función para mostrar estado
void mostrar(struct Luces luces) {
    printf("Estado: [%d %d %d %d %d %d %d %d]\n",
        luces.l1, luces.l2, luces.l3, luces.l4,
        luces.l5, luces.l6, luces.l7, luces.l8);
}

int main() {
    struct Luces panel = {0}; // todas apagadas

    mostrar(panel);

    // Encender algunas luces
    panel.l1 = 1;
    panel.l4 = 1;
    panel.l8 = 1;

    mostrar(panel);

    // Apagar una luz
    panel.l4 = 0;

    mostrar(panel);

    return 0;
}
