
Que es una estructura? Tipo de dato
para que me sirve o cuando las uso? 


#include <stdio.h>

struct un_auto{
    short cant_puertas;
    char color[20];
    float valor;
    short rodado;
};

int main(void)
{
    struct un_auto mi_auto;
    //mi_auto.color = "Azul";
    strncpy(mi_auto.color, "Azul", 20);
    mi_auto.cant_puertas = 4;
    mi_auto.rodado = "25";
    mi_auto.valor = 100000.50;

    printf("Valor: %.2f \n", mi_auto.valor);
    printf("Color: %s \n", mi_auto.color);

    return 0;
}


--------------------------------------------------------------------------
--------------------------------------------------------------------------


#include <stdio.h>

struct conductor{
    char nombre[100];
    long dni;
    float sueldo;
};

struct un_auto{
    short cant_puertas;
    char color[20];
    float valor;
    short rodado;
    struct conductor chofer[2];
};

int main(void)
{
    struct un_auto mi_auto[2];
    //mi_auto.color = "Azul";
    strncpy(mi_auto[0].color, "Azul", 20);
    mi_auto[0].cant_puertas = 5;
    mi_auto[0].rodado = "25";
    mi_auto[0].valor = 100000,50;
    mi_auto[0].chofer[0].dni = 30111222;
    mi_auto[0].chofer[1].dni = 22444555;

    strncpy(mi_auto[1].color, "Rojo", 20);
    mi_auto[1].cant_puertas = 3;
    mi_auto[1].rodado = "25";
    mi_auto[1].valor = 90000,50;
    mi_auto[0].chofer[0].dni = 20444555;
    mi_auto[0].chofer[1].dni = 10555444;


    printf("Valor: %.2f \n", mi_auto[0].valor);
    printf("Color: %s \n", mi_auto[0].color);
    printf("DNI Chofer 1: %ld \n", mi_auto[0].chofer[0].dni);
    printf("DNI Chofer 2: %ld \n\n", mi_auto[0].chofer[1].dni);

    printf("Valor: %.2f \n", mi_auto[1].valor);
    printf("Color: %s \n", mi_auto[1].color);


    return 0;
}

