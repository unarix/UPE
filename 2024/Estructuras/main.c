#include <stdio.h>

struct conductor{
    char nombre[100];
    long dni;
    float sueldo;
};

struct automovil{
    short cant_puertas;
    char color[20];
    float valor;
    short rodado;
    struct conductor chofer[2];
};

int main(void)
{
    int i=0;
    int j=0;
    struct automovil mi_auto[2];
    //mi_auto[0].color = "Azul";
    strncpy(mi_auto[0].color, "Azul", 20);
    mi_auto[0].cant_puertas = 5;
    mi_auto[0].rodado = "25";
    mi_auto[0].valor = 10000,50;
    mi_auto[0].chofer[0].sueldo = 50000,00;
    strncpy(mi_auto[0].chofer[0].nombre, "Ivan", 100);
    mi_auto[0].chofer[1].sueldo = 58000,00;
    strncpy(mi_auto[0].chofer[1].nombre, "Julio", 100);

    strncpy(mi_auto[1].color, "Rojo", 20);
    mi_auto[1].cant_puertas = 4;
    mi_auto[1].rodado = "25";
    mi_auto[1].valor = 20000,50;
    mi_auto[1].chofer[0].sueldo = 56000,00;
    strncpy(mi_auto[1].chofer[0].nombre, "Fernando", 100);
    mi_auto[1].chofer[1].sueldo = 56700,00;
    strncpy(mi_auto[1].chofer[1].nombre, "Mariano", 100);

    for(i=0;i<2;i++)
    {
        printf("Auto: %hd \n", i);
        printf("    El Valor es: %f \n", mi_auto[i].valor);
        printf("    El Color es: %s \n", mi_auto[i].color);
        for(j=0;j<2;j++)
        {
            printf("    Chofer: %hd \n", j);
            printf("        El Nombre del chofer es: %s \n", mi_auto[i].chofer[j].nombre);
            printf("        El Sueldo del chofer es: %f \n", mi_auto[i].chofer[j].sueldo);
        }
    }

    return 0;
}
