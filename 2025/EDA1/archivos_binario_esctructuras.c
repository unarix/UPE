// Ahora vamos a combinar lo que vimos recien pero con estrcuturas para que sea mas facil el manejo
// El mecanismo de lectrua de un binario y volcarlo a nuestra estrcutura tambien se denomina deserializacion
// En cambio el volcado de memoria a un archivo se llama serializacion

#include<stdio.h>
#include<string.h>

// Hahamos una estructura cualquiera
// como la hago a la estrctura? si quiero que contenga el nombre y apellido de un alumno? 
struct info{
    char nombre[40];
    char apellido[40];
};

int main()
{
    FILE *archivo;
    struct info datos;

	// Como asigno un nombre a una variable string? 
    strcpy(datos.nombre,"Pedro");
    strcpy(datos.apellido,"Tello");

    if((archivo = fopen("TEST.bin","wb"))!= NULL)
    {
        fwrite(&datos,sizeof(datos),1,archivo);
        fclose(archivo);
        printf("El archivo fue guardado ok\n");
    }
	
	// Leerlo!
    if((archivo = fopen("TEST.bin","rb"))!= NULL)
    {
        fread(&datos,sizeof(datos), 1, archivo);
        fclose(archivo);
    }

    printf("Nombre : %hs\n", datos.nombre);
    printf("Apellido : %hs\n", datos.apellido);

    return 0;
}

// Y si quiero que sea un vector de estructuras?

#include<stdio.h>
#include<string.h>

struct info{
    char nombre[40];
    char apellido[40];
};

int main()
{
    FILE *archivo;
    struct info datos[2];

	  // Como asigno en una estructura?
    strcpy(datos[0].nombre,"Pedro");
    strcpy(datos[0].apellido,"Tello");
    strcpy(datos[1].nombre,"Nahuel");
    strcpy(datos[1].apellido,"Tellox");

    if((archivo = fopen("TEST.bin","wb"))!= NULL)
    {
        fwrite(&datos,sizeof(datos),1,archivo);
        fclose(archivo);
        printf("El archivo fue guardado ok\n");
    }

	  // Leerlo!
    if((archivo = fopen("TEST.bin","rb"))!= NULL)
    {
        fread(&datos,sizeof(datos), 1, archivo);
        fclose(archivo);
    }

    printf("Nombre : %hs\n", datos[0].nombre);
    printf("Apellido : %hs\n", datos[0].apellido);
    printf("Nombre : %hs\n", datos[1].nombre);
    printf("Apellido : %hs\n", datos[1].apellido);

    return 0;
}

