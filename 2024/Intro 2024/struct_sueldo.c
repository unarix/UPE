// Vallamos a algo mas practico: las funciones se suelen utilizar para realizar operaciones 
// que luego podamos reutilizar en cualquier otra parte de nuestro codigo
// y para encapsular, una determinada funcionalidad... como ya explico gustavo. 

// Entonces: 
// Queremos hacer una funcion que a partir del sueldo bruto DE UN EMPLEADO nos retorne el sueldo neto (hagamos solo con horas extra)
// que nos retorne el objeto empleado completo.
// Basicamente quiero pasarle el struct empleado... que se haga la cuenta y me lo retorne con el calculo del sueldo hecho. 

// COMO DATOS DE LA PERSONA Debo ingresar:
// DNI
// Sueldo
// Horas extras

#include <stdio.h>

struct persona {
    long DNI;
    float sueldo;
    short h_extras;
};

struct persona calcularSueldo(struct persona emp);

int main(void)
{
    struct persona empleado;

    // Ingresamos los datos del empleado
    printf("Ingrese el DNI: \n");
    scanf("%ld", &empleado.DNI);
    printf("Ingrese el sueldo bruto: \n");
    scanf("%f", &empleado.sueldo);
    printf("Ingrese horas extras: \n");
    scanf("%hd", &empleado.h_extras);

   
    empleado = calcularSueldo(empleado);

    // Imprimimos los datos del empleado
    printf("\n ** Sueldo de este mes: ** \n");
    printf("  DNI: %ld\n",empleado.DNI);
    printf("  Sueldo: %.3f \n",empleado.sueldo);
        
    return 0;
}

// Agrgear el calculo de impuestos *0.17 o *17/100
struct persona calcularSueldo(struct persona emp)
{
    short hora_neta = (emp.sueldo / 21) / 8;
    emp.sueldo = emp.sueldo + (hora_neta * emp.h_extras);
    return emp;
}
