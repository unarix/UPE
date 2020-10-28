#include<stdio.h>
#define cantidad 3

// Declaramos la estructura con sus atributos y la llamamos "caja"
struct caja
{
    char cliente[50]; // tipo char de 50 posiciones.
    short alto;
    short ancho;
    short peso;
};

int main(void)
{
    struct caja cajas[cantidad]; // Inicializamos un vector que se llamara "cajas" y sera del tipo "caja"
    short i=0;

    printf("Bienvenido al sistema *Cajita IN/OUT* \n"); // printf: nos permite mostrar texto en la consola

    for (i=0;i<cantidad;i++)
    {
        printf("Carga de datos para el cliente %hd: \n",i+1); // Porque i+1? Porque queremos mostrar el orden del cliente que cargamos... la variable I al inicio esta en cero.
        printf(" > Ingrese el nombre del cliente: ");
        scanf("%s", cajas[i].cliente);  // scanf: nos permite obtener texto desde la consola
                                        // &cajas[i].cliente: guardamos lo que obtenemos desde la consola en la posicion "i" del vector de cajas y dentro el atributo cliente
        printf(" > Ingrese el alto de la caja: ");
        scanf("%hd", &cajas[i].alto);
        printf(" > Ingrese el ancho de la caja: ");
        scanf("%hd", &cajas[i].ancho);
        printf(" > Ingrese el peso de la caja: ");
        scanf("%hd", &cajas[i].peso);
        printf(" \n"); // Salto de linea para separar el texto del próximo cliente

        i = i++; // Sumamos 1 al contador de posición del vector
    }

    // Imprimimos el listado de las cajas que se cargaron:

    printf("*** Listado de cajas: ***\n\n");

    for (i=0;i<cantidad;i++)
    {
        printf(" > Cliente %s \n", cajas[i].cliente);
        printf("   Alto Caja %d \n", cajas[i].alto);
        printf("   Ancho Caja %d \n", cajas[i].ancho);
        printf("   Peso Caja %d \n", cajas[i].peso);
        printf(" \n");
    }

    // Finalizamos la función.
    return(0);
}