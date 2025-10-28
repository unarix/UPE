#include <stdio.h>
#include <stdlib.h>   // Para system()
#include <unistd.h>   // Para sleep() en Linux/Mac
// Si usás Windows, cambiá sleep(segundos) por Sleep(milisegundos) y agrega: #include <windows.h>

int main() {
    int i;

    printf("Cargando: [");
    fflush(stdout); // Forzamos que se muestre el texto antes del bucle

    for (i = 1; i <= 5; i++) {
        printf("#");
        fflush(stdout); // Actualiza la salida en cada paso
        sleep(1);       // Espera 1 segundo (cambiar por 0 o menos para hacerlo más rápido)
    }

    printf("] 100%%\n");
    printf("Carga completa\n");

    return 0;
}
