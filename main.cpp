#include<stdio.h>

struct caja
{
    char cliente[50];
    int alto;
    int ancho;
    int peso;
    char fragil;
};

void imprimir(caja cajas[], int cant); 

int main(void)
{
    int cant = 0;
    caja cajas[100];
    int i = 0;
    char continuar = 's';
    int altomax = 120;
    int altoaux = 0;

    printf("Bienvenido al sistema *Cajita IN/OUT* \n");

    while(continuar == 's') 
    {
        printf(">> Carga de datos para el cliente %d: \n",i+1);
        printf(" > Ingrese el nomble del cliente: "); 
        scanf("%s", cajas[i].cliente);  
        printf(" > Ingrese el alto de la caja: ");
        scanf("%d", &altoaux);
        printf(" > Ingrese el ancho de la caja: ");
        scanf("%d", &cajas[i].ancho);
        printf(" > Ingrese el peso de la caja: ");
        scanf("%d", &cajas[i].peso);
        printf(" \n"); // Salto de linea para separar el texto del proximo cliente

        i = i+1; // Sumamos 1 al contador de posicion del vector

        // Valido que no supere el maximo de altura
        if( altoaux < altomax)
        {
            altoaux = cajas[i].alto;
        }
        else
        {
            printf("Alto supera el maximo, se descarta la caja. \n");
            i= i-1; //Resto una posicion, para que en el proximo bucle sea reemplazada.
        }

        // Si pesa menos de 570g la marco como fragil.
        if (cajas[i].peso < 570)
        {
            cajas[i].fragil = 's';
        }
        

        printf(">> Quiere continuar la carga? (s/n): "); // printf: nos permite mostrar texto en la consola
        scanf("%s", &continuar);  // scanf: nos permite obtener texto desde la consola
        printf(" \n");

        cant = i; // Guardo la cantidad de cajas que fueron cargadas
    }

    imprimir(cajas, cant); 
    // Importante: 
    // Como se ve arriba, a la funcion "imprimr" le envio la variable "cant" en el parametro de cantidad asignado por "i",
    // esta variable contiene la cantidad de posiciones que se llenaron en el array.. de lo contrario imprimira las 100 posiciones.

    return(0);
}

/// Esta funcion me permite imprimr el vector de cajas en pantalla
void imprimir(caja cajas[], int cant)
{   
    int i=0;

    printf("*** Listado de cajas: ***\n\n");

    for (i=0;i<cant;i++)
    {
        printf(" > Cliente %s \n", cajas[i].cliente);
        printf("   Alto Caja %d \n", cajas[i].alto);
        printf("   Ancho Caja %d \n", cajas[i].ancho);
        printf("   Peso Caja %d \n", cajas[i].peso);
        printf("   Fragil %c \n", cajas[i].fragil);
        printf(" \n");
    }

}