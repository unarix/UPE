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

    strcpy(datos.nombre,"Nahuel");
    strcpy(datos.apellido,"Tello");

    if((archivo = fopen("TEST.$$$","wb"))!= NULL)
    {
        fwrite(&datos,sizeof(datos),1,archivo);
        
        // Que pasa si vuelvo a escribir?
        strcpy(datos.nombre,"Pedro");
        strcpy(datos.apellido,"Gomez");
        fwrite(&datos,sizeof(datos),1,archivo);

        fclose(archivo);
        // Que pasa si escribo de nuevo pero lo cerre antes? Se rompe?
        strcpy(datos.nombre,"Alejandro");
        strcpy(datos.apellido,"Perez");
        fwrite(&datos,sizeof(datos),1,archivo);
    }

    printf("El archivo fue guardado\n");

    return 0;
}