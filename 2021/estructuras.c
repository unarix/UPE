#include<stdio.h>

// Struct es un tipo de dato... asi como el short, float, char, y demas... es lo mismo es un tipo de dato... pero para que sirve?? 
// que nos permite??? 
// Nos permite agrupar informacion, osea... toda la informacion que se trate de lo mismo (en simples palabras) la puedo agrupar en un struct.

// El Struct es la punta de la programacion orientada a objetos... donde estas estrcutras son objetos que se llaman entidades.
// El Ejemplo de una entidad Auto es un auto... y que atributos tiene un auto? 
// Como pueden describir a un auto? 

// Entonces basicamente es un agrupador de datos dentro de una estructura.
// Es una muy buena forma de almacenar datos en archivos binarios.
// Se define siempre de forma Global, para poder intercambiar las estructuras entre distintas funciones.
// La declaracion de la estructura no ocupa espacio, salvo cuando la instanciamos dentro de una variable... recien ahi esta alocando memoria.

// NO PONER EN EL PRIMER EJ // ESTRUCTURAS ANIDADAS
struct casa{
    short codigo_postal;
    short direccion_altura;
};

struct persona{ // < -- strcut empleado es el tipo de dato
    short edad;
    long DNI;
    float sueldo;
    
    // NO PONER EN EL PRIMER EJ
    struct casa domicilio; 
}; // <-- NO OLVIDAR NUNCA EL PUNTO Y COMA!!!


int main(void)
{
    struct persona empleado; // <-- persona, es el identificador, es la variable... el resto es el tipo de dato

    empleado.DNI = 40111222; // <-- Notar que es el nombre de la variable PUNTO el campo de la estructura.
    empleado.edad = 22;
    empleado.sueldo = 35000.50;

    // Vamos a imprimirlo: 
    printf("Datos del empleado: \n");
    printf("  - Edad: %hd \n", empleado.edad);
    printf("  - DNI: %ld \n", empleado.DNI);
    printf("  - Sueldo: %f \n", empleado.sueldo);


    printf("EJEMPLO 2: \n");

    // Ahora vamos antes de imprimirlo solicitar al usuario que cargue los datos del empleado y luego imprimirlos: 
    printf("Ingrese edad: \n");
    scanf("%hd", &empleado.edad);
    printf("Ingrese DNI: \n");
    scanf("%ld", &empleado.DNI);
    printf("Ingrese Sueldo: \n");
    scanf("%F", &empleado.sueldo);
    // Lo imprimimos:
    printf("Datos del empleado: \n");
    printf("  - Edad: %hd \n", empleado.edad);
    printf("  - DNI: %ld \n", empleado.DNI);
    printf("  - Sueldo: %.2f \n", empleado.sueldo);


    printf("EJEMPLO 3: \n");

    // Hagamos un ejer: 
    // Ademas de los datos ya cargados,
    // Se debe cargar el domicilio del empleado teniendo en cuenta que una casa no es la misma entidad que persona
    // Como se hace esto? con estructuras anidadas.
    // Entonces vamos a cargar de nuevo esta estructura: 
    printf("Ingrese los datos del empleado: \n");
    printf("Ingrese edad: \n");
    scanf("%hd", &empleado.edad);
    printf("Ingrese DNI: \n");
    scanf("%ld", &empleado.DNI);
    printf("Ingrese Sueldo: \n");
    scanf("%F", &empleado.sueldo);

    printf("Ingrese los datos del domicilio: \n");
    printf("  Ingrese Cod Postal: \n");
    scanf("%hd", &empleado.domicilio.codigo_postal);
    printf("  Ingrese Altura: \n");
    scanf("%hd", &empleado.domicilio.direccion_altura);
    
    printf("Los datos del empleado son: \n");
    printf("  - Edad: %hd \n", empleado.edad);
    printf("  - DNI: %ld \n", empleado.DNI);
    printf("  - Sueldo: %.2f \n", empleado.sueldo);
    printf("    - Domicilio CP: %hd \n", empleado.domicilio.codigo_postal);
    printf("    - Domicilio altura: %hd \n", empleado.domicilio.direccion_altura);
    
    return 0;
}
