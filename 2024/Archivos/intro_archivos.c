#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    // Que es un archivo en sistemas?
    // Que atributos tiene un archivo?
    // Que tipos de archivos conocen? video/audio/word/texto etc
    // Que extenciones tienen esos archivos? 
    // y cual es el formato de un archivo de musica por ejemplo? MPEG-1 Audio Layer III o MPEG-2 Audio Layer III,
    // Cuanto solia pesar un archivo del tipo MP3? 
    // y que seria la ubicacion del archivo? 
    // Entonces ya nos dimnos cuenta que son dos tipos, binarios y de texto. 
	
	// Que pasa cuando ustedes cierran el programa hoy? pierden todo. 
	// con esto podrian gaurdar lo que hicieron y levantarlo cuando vuelvan a abrir el prog para continuar.

    // Para poder manejar un archivo, lo primero que debemos conocer es la estructura File
    // Esta estructura tiene la informacion del archivo que estamos levantando.
    // FILE *archivo; //File es una estructura . Creamos un puntero tipo File

    // Para poder abrir un archivo utilizamos fopen
    // archivo = fopen("mensaje.txt","wt");//escribe/texto
	
	//“r” : abrir un archivo para lectura, el archivo debe existir.
	//“w” : abrir un archivo para escritura, se crea si no existe o se sobreescribe si existe.
	//“a” : abrir un archivo para escritura al final del contenido, si no existe se crea.
	//“r+” : abrir un archivo para lectura y escritura, el archivo debe existir.
	//“w+” : crear un archivo para lectura y escritura, se crea si no existe o se sobreescribe si existe.
	//“r+b ó rb+” : Abre un archivo en modo binario para actualización (lectura y escritura).
	//“rb” : Abre un archivo en modo binario para lectura.

    // Para poder cerrar un archivo usamos fclose:
    // fclose(archivo);
	// Porque tenemos que cerrarlo? porque cuando un programa usa un archivo, lo hace de modo exclusivo. 
	// Alguna vez les paso que un archivo se les quedo bloqueado y tuvieron que reiniciar la PC para que se libere. 


    // Entonces, supongamos que yo quiero escribir en un archivo una cadena de texto:
	FILE *archivo; 
	
    char msg[] = "Hola...\n\nEsto contiene el archivo de texto!!\n\n";
    int i = 0;
    //si el archivo existe lo sobreescribe
    //hay que crear una funcion que verifique esto de ser necesario
    archivo = fopen("mensaje.txt","wt");//escribe/texto

    // Debemos siempre verificar que el arrchivo se pudo abrir y que existe:
    if(archivo == NULL)
    {
        printf("ERROR de creacion");
        exit(0);//si hay error termina el programa
    }
    // COmo escribimos el texto en el archivo:
    fputs(msg,archivo); //Escribe la cadena en el archivo

    // finalmente cerramos el arhivo
    fclose(archivo);
    return 0;
	
	// DONDE SE LES OCURRE QUE HOY EN DIA SE SIGUE USANDO ESTO MUCHISIMO? 
	
}
