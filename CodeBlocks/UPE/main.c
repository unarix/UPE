#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Seteo de Formato de datos
struct Datos
{
    char Nombre[6];
    long Cantidad;
    long Longitud;
    long Precio;
    char Color[8];
};
short i=-1;
short c;
struct Datos cable[20];


int main(void)
{

    short x;

    //Menu
    do
    {
        printf("---------------------------------------\n"
               "Base de Datos\n"
               "OPCIONES:\n "
               "1-Ingresar nuevo cable\n "
               "2-Buscar un cable\n "
               "3-Listado de cables\n "
               "4-Vender un cable\n "
               "5-Comprar cable\n "
               "0-Salir del programa\n"
               "OPCION: ");

        scanf("%hd",&x);
        switch(x)
        {
        case 0:
            printf("\nNos vemos luego\n");
            break;

        case 1:
            printf("\nIngreso de nuevo cable\n");
            i++;
            Ingreso();
            break;

        case 2:
            printf("\nBusqueda de cables\n");
            Busqueda();
            break;

        case 3:
            printf("\nListado de cable\n");
            listado();
            break;

        case 4:
            printf("\nVender un cable\n");
            Venta();
            break;

        case 5:
            printf("\nComprar un cable\n");
            Compra();
            break;

        default:
            printf("\nLa opcion ingresada no es valida\nIntente nuevamente\n\n");
            break;
        }

    }
    while(x!=0);
    return 0;
}

void Ingreso()///Ingreso de nuevos cables
{
    if(i>20)
    {
        printf("\nNo se pueden ingresar mas cables.\n");
    }
    else
    {

        printf("\nCable numero %hd:\n",i+1);
        printf("Nombre: ");
        scanf("%s",cable[i].Nombre);

        printf("Cantidad: ");
        scanf("%ld",&cable[i].Cantidad);

        printf("Longitud del cable: ");
        scanf("%ld",&cable[i].Longitud);
        while(cable[i].Longitud>200)
        {
            printf("No existe cable con una longitud mayor a 200, Ingrese nuevamente el valor:");
            scanf("%ld",&cable[i].Longitud);
        }

        printf("Precio: ");
        scanf("%ld",&cable[i].Precio);

        printf("Color: ");
        scanf("%s",cable[i].Color);

        printf("\nNuevo cable ingresado en la base de datos\n");
    }

}
void Busqueda()
{
    char busc[6];
    short flag=0;

    printf("\nIngrese nombre del cable buscado: ");
    scanf("%s",busc);

    for(c=0; c<=i; c++)
    {

        if(strcmp(busc, cable[c].Nombre) == 0)
        {
            printf("\nResultado coincidente: Cable #%hd\n", c+1);
            printf("\nNombre: %s\nCantidad: %ld\nLongitud: %ld\nPrecio: %ld\nColor: %s\n\n",cable[c].Nombre,cable[c].Cantidad,cable[c].Longitud,cable[c].Precio,cable[c].Color);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("No se encontro un cable con ese nombre\n");
    }

}
void listado()
{
    if(i!=-1)
    {
        short cant;

        printf("\nIngrese cantidad de stock a filtrar: ");
        scanf("%hd", &cant);
        if(cable[c].Cantidad < cant)
        {
            printf("\nLista de cables con stock menor a %hd:\n",cant);

            for(c=0; c<=i; c++)
            {
                if(cable[c].Cantidad < cant)
                {
                    printf("-----------------------");
                    printf("\n\nCable #%hd\n",c+1);
                    printf("\nNombre: %s\nCantidad: %ld\nLongitud: %ld\nPrecio: %ld\nColor: %s\n\n",cable[c].Nombre,cable[c].Cantidad,cable[c].Longitud,cable[c].Precio,cable[c].Color);
                }

            }
        }
        else
        {
            printf("\nNo hay cables en la base datos con stock menor a %hd\n",cant);
        }
    }
    else
    {
        printf("No se han ingresado cables en la base de datos\n");
    }
}
void Venta()
{

    char vent[6];//Nombre del cable a vender
    short cantv;//cantidad Vendida
    short IVA;//Calculo del iva
    short pfinal;//Precio final
    short flag=0;

    printf("\nIngrese el nombre del cable que desea vender: ");
    scanf("%s",vent);


    for(c=0; c<=i; c++)
    {

        if(strcmp(vent, cable[c].Nombre) == 0)
        {
            printf("\nResultado coincidente: cable #%hd\n", c+1);
            printf("\nIngrese la cantidad a vender: ");
            scanf("%hd",&cantv);

            if(cantv<cable[c].Cantidad)
            {
                flag=1;
                cable[c].Cantidad=cable[c].Cantidad-cantv;
                IVA=(cable[c].Precio*cantv)*0.21;
                pfinal=(cable[c].Precio*cantv)+IVA;
                printf("Cantidad despues de la venta %ld\n",cable[c].Cantidad);
                printf("Precio final: $%hd\n\n",pfinal);

            }
            else
            {
                flag=1;
                printf("No se tiene cable suficiente para realizar la venta. Cantidad en stock %ld\n",cable[c].Cantidad);
            }
        }

    }
    if(flag==0)
    {
        printf("No se encontro un cable con ese nombre\n\n");
    }


}
void Compra()
{

    char compra[6];//Nombre del cable a comprar
    short cantc;//cantidad comprada
    short flag=0;

    printf("\nIngrese el nombre del cable que desea comprar: ");
    scanf("%s",compra);

    for(c=0; c<=i; c++)
    {
        if(strcmp(compra, cable[c].Nombre) == 0)
        {
            flag=1;
            printf("\nResultado coincidente: cable #%hd\n", c+1);
            printf("\nIngrese la cantidad a comprar: ");
            scanf("%hd",&cantc);
            cable[c].Cantidad=cable[c].Cantidad+cantc;
            printf("Cantidad despues de la compra %ld\n",cable[c].Cantidad);
        }
    }
    if(flag==0)
    {
        printf("No se encontro un cable con ese nombre\n\n");
    }

}


