#include <stdio.h>
#define CANT 2
struct persona {
    char nombre[20];
    long DNI;
    float sueldo;
    short h_extras;
};

float calcularSueldo(struct persona emp);

int main(void)
{
    struct persona empleados[CANT];;
    short i=0;
    short cont = 0;

    do
    {
       // Ingresamos los datos del empleado
        printf("Ingrese el nombre del empleado: \n");
        scanf("%s", empleados[cont].nombre);
        printf("Ingrese el DNI: \n");
        scanf("%ld", &empleados[cont].DNI);
        printf("Ingrese el sueldo bruto: \n");
        scanf("%f", &empleados[cont].sueldo);
        printf("Ingrese horas extras: \n");
        scanf("%hd", &empleados[cont].h_extras);

        empleados[cont].sueldo = calcularSueldo(empleados[cont]);
        cont++;

    } while(cont<CANT);


    // Imprimimos los datos de los empleados
    for (i=0;i<CANT;i++)
    {
        printf("\n ** Sueldo de este mes para %s: ** \n", empleados[i].nombre);
        printf("  DNI: %ld\n",empleados[i].DNI);
        printf("  Sueldo: %.3f \n",empleados[i].sueldo);
    }

    printf("\n ** Los empleados que deben pagar impuesto a las ganancias son: ** \n");
    for (i=0;i<CANT;i++)
    {
        if(empleados[i].sueldo>10000)
        {
            printf(" - %s, debe pagar ganancias! \n", empleados[i].nombre);
        }
    }

    return 0;
}

// Agrgear el calculo de impuestos *0.17 o *17/100
float calcularSueldo(struct persona emp)
{
    short hora_neta = (emp.sueldo / 21) / 8;
    float sueldo = emp.sueldo + (hora_neta * emp.h_extras);
    return sueldo;
}
