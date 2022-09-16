#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    FILE *archivo;
    char msg[] = "Hola...\n\nEsto contiene el archivo de texto!!\n\n";
    int i = 0;
    //si el archivo existe lo sobreescribe
    //hay que crear una funcion que verifique esto de ser necesario
    archivo = fopen("mensaje.txt","wt");//escribe/texto
    if(archivo == NULL)
    {
        printf("ERROR de creacion");
        exit(0);//si hay error termina el programa
    }
    fputs(msg,archivo); //Escribe la cadena en el archivo
    fclose(archivo);
    return 0;
}