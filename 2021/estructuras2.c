#include <stdio.h>

struct fecha{
    unsigned short dia;
    unsigned short mes;
    unsigned short anio;
};

struct ficha{
    unsigned short edad;
    float sueldo;
    struct fecha nacimiento;
};

int main(void)
{
    struct ficha p;
    p.edad=25;
    p.sueldo=18745.25;
    p.nacimiento.dia=18;
    p.nacimiento.mes=9;
    p.nacimiento.anio=1947;
    printf("Edad: %hu\n",p.edad);
    printf("Sueldo: $%.2f\n",p.sueldo);
    printf("Fecha de nacimiento %hu/%hu/%hu\n\n",p.nacimiento.dia,p.nacimiento.mes,p.nacimiento.anio);
    return 0;
}
