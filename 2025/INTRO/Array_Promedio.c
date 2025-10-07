/*
 Ejercicio básico en lenguaje C donde el usuario carga un vector (array) de 10 posiciones
 y luego se calcula y muestra el promedio de los valores ingresados

 Vemos:
 - Uso de arrays
 - Uso de bucles for
 - Entrada y salida de datos con scanf y printf
 - Cálculo de promedio
 - Conversión de tipos (casting de int a float)
*/

#include <stdio.h>

int main() {
    short numeros[10];          // Vector de 10 enteros
    short suma = 0;             // Variable para acumular la suma
    float promedio;           // Variable para almacenar el promedio

    // Cargar el vector con valores ingresados por el usuario
    printf("Ingrese 10 numeros enteros:\n");
    for(short i = 0; i < 10; i++) {
        printf("Numero %hd: ", i + 1);
        scanf("%d", &numeros[i]);
        suma += numeros[i];  // Sumar el número ingresado
    }

    // Calcular el promedio
    promedio = (float)suma / 10;

    // Mostrar el resultado
    printf("\nEl promedio de los numeros ingresados es: %.2f\n", promedio);

    return 0;
}
