#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    FILE *archivo;
    char msg1[] = "Hola...\n\nEsto contiene el archivo de texto!!\n\n";
    char msg2[100];
    int i = 0;
    archivo = fopen("mensaje.txt", "at");

    if(archivo == NULL)
    {
        printf("ERROR de lectura");
        exit(0); //si hay error termina el programa
    }

    fputs(msg1,archivo);
    printf("El archivo fue escrito. \n");
    fclose(archivo);
    printf("Archivo cerrado. \n");

    archivo = fopen("mensaje.txt", "rt");
    printf("Leyendo el archivo:  \n");
    while(!feof(archivo))
    {
        fgets(msg2, 100, archivo);
        printf("%hd %s", i, msg2);
        i++;
    }
    printf("\n La informacion fue leida en %hd veces\n\n", i);
    fclose(archivo);
    return 0;
}
