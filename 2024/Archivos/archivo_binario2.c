#include<stdio.h>
#include<string.h>

struct info{
    char nombre[40];
    char apellido [40];
};

int main()
{
    FILE *archivo;
    struct info datos;

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
