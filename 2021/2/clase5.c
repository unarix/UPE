#include <stdio.h>

struct fecha{
    short dia;
    short mes;
    short anno;
};

struct casa {
    short codigo_postal;
    short altura;
    short piso;
    char depto;
    struct fecha construccion;
};

struct persona {
    short edad;
    long DNI;
    float sueldo;
    struct casa domicilio;
    struct fecha nacimiento_fecha;
};

int main(void)
{
    struct persona empleado;

    // Ingresamos los datos del empleado
    printf("Ingrese el DNI: \n");
    scanf("%ld", &empleado.DNI);
    printf("Ingrese la edad: \n");
    scanf("%hd", &empleado.edad);
    printf("Ingrese el sueldo: \n");
    scanf("%f", &empleado.sueldo);

    printf("Ingrese el CP: \n");
    scanf("%hd", &empleado.domicilio.codigo_postal);
    printf("Ingrese la altura del domicilio: \n");
    scanf("%hd", &empleado.domicilio.altura);
    printf("Ingrese el piso: \n");
    scanf("%hd", &empleado.domicilio.piso);
    printf("Ingrese el depto: \n");
    scanf(" %c", &empleado.domicilio.depto);
    fflush(stdin);
    // Hacer: pedir el dia de nacimiento del empleado
    empleado.nacimiento_fecha.dia = 28; // a modo de ejemplo, igualamos el dia en 28, pero debemos pedirlo
    printf("Ingrese el anio de nac: \n");
    scanf("%hd", &empleado.nacimiento_fecha.anno);
    // Hacer: pedir el mes de nacimiento del empleado

    // Imprimimos los datos del empleado
    printf("\n ** Datos del empleado: ** \n");
    printf("  Edad: %hd\n", empleado.edad);
    printf("  DNI: %ld\n",empleado.DNI);
    printf("  Sueldo: %.3f \n",empleado.sueldo);
    printf("  El depto es: %hd %c \n",empleado.domicilio.piso,empleado.domicilio.depto);
    printf("  La fecha de nacimiento es: %hd/%hd \n\n",empleado.nacimiento_fecha.dia, empleado.nacimiento_fecha.anno); //Imprimir la fecha completa
    
    return 0;
}