#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    // Que es un archivo en sistemas? Un archivo es una unidad lógica de almacenamiento de datos
    // Que atributos tiene un archivo? Nombre/ extencion / ruta / permisos / fechas / solo lectura / oculto / etc
    // Que tipos de archivos conocen? notepad/video/audio/word etc
    // Que extenciones tienen esos archivos? txt / avi / mpg / doc
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
	//“a” : abrir un archivo para escritura al final del contenido, si no existe se crea (APPEND).
	//“r+” : abrir un archivo para lectura y escritura, el archivo debe existir.
	//“w+” : crear un archivo para lectura y escritura, se crea si no existe o se sobreescribe si existe.
	//“r+b ó rb+” : Abre un archivo en modo binario para actualización (lectura y escritura).
	//“rb” : Abre un archivo en modo binario para lectura.

    // Para poder cerrar un archivo usamos fclose:
    // fclose(archivo);
	// Porque tenemos que cerrarlo? porque cuando un programa usa un archivo, lo hace de modo exclusivo. 
	// Alguna vez les paso que un archivo se les quedo bloqueado y tuvieron que reiniciar la PC para que se libere. 

	// **********************************************************
	// Bueno entonces vamos de a poquito... 
	// Primero vamos a crear un archivo y agregarle un texto
	// Despues vamos a abrir ese mismo archivo agregarle mas texto (append), porque es lo mas comun y normal.
	// Y por ultimo a ese archivo vamos a leerlo y mostrar la informacion por pantalla.
	// **********************************************************

    // Entonces, supongamos que yo quiero escribir en un archivo una cadena de texto cualquiera... 
	// Lo primero que tengo que hacer es crear un puntero a la estructura FILE.
	FILE *archivo; 
	// porque? porque es lo que va a representar al archivo en mi programa... 
	
	// Lo segundo que necesito es algo que quiera escribir en ese arhico... 
	// como creo un string?
    char msg[] = "Hola...\n\nEsto contiene el archivo de texto!!\n\n";
	
	// Y lo tercero que necesito es abrir ese archivo o crearlo... 
	// Eso lo hacemos con fopen y FOPEN me poermite hacerlo de distintos modos.
    archivo = fopen("mensaje.txt","wt"); //escribe/texto, el T no es del todo necesario porque en el estandard acctual T es por defecto.
	// READ / WRITE / APPEND 
	// EL + Sube un nivel pero en el caso de read el archivo debe existir.
	// SUMANDO LA B, indico que lo abra en modo binario.

    // algo importante es que debemos siempre verificar que el arrchivo se pudo abrir y que existe:
	// Puede pasar que el archivo este bloqueado o en uso por otra persona o algun otro programa
    if(archivo == NULL)
    {
        printf("ERROR de creacion");
        exit(0);//si hay error termina el programa
    }
    // COmo escribimos el texto en el archivo:
    fputs(msg,archivo); //Escribe la cadena en el archivo

    // finalmente cerramos el arhivo
    fclose(archivo); // Es muy importante porque Asegura que los datos se escriban
    return 0;
	
	// DONDE SE LES OCURRE QUE HOY EN DIA SE SIGUE USANDO ESTO MUCHISIMO? 
	
}

// Ahora vamos a mejorar lo anterior y vamos a agregarle texto al mismo archivo que habiamos generado... 

#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	FILE *archivo;

    char msg[] = "Agrego mas texto! \n\n"; // MODIFICO EL TEXTO

    archivo = fopen("mensaje.txt","a"); //que tengo que cambiar aca si quiero agregar texto? Append!

    if(archivo == NULL) // siempre comprobamos que el archivo existe... 
    {
        printf("ERROR de creacion");
        exit(0);
    }

	// como se les ocurre que agrego mas texto? 
	// me sirve la misma funcion? 
	// fputs escribe siempre que tenga los permisos (probar con r solo)
	// Pero guarda porque no me avisa nada!
    fputs(msg,archivo); 

    fclose(archivo);
    return 0;
}


// Ahora vamos a leer lo que en el archivo anterior habiamos escrito, esto lo podemos hacer con fgets.
// y vamos a entender como lee fgets
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	FILE *archivo;
	char msg[100];
    short i = 0; // Contador para saber cuantas lineas leyo

    archivo = fopen("mensaje.txt", "r"); // que tengo que cambiar para solo leer?
    printf("Leyendo el archivo:  \n");

	// Para poder leer fgets lee linea por linea... cuando termina de leer una linea mueve el cursor a la siguiente.
	// se da cuenta que termino la linea por el \n	
	// entonces para leer todo el archivo que tiene varias lineas, debemos preguntar si no llego al fin del archivo. (FEOF!) 
    while(!feof(archivo)) // Mientras no sea el fin del archivo
    {
		// msg, donde guarda
		// sizeoff, numero maximo de caracteres que voy a leer de esa linea.
		// archivo es la fuente de lectura
        fgets(msg, sizeof(msg), archivo); // obtengo el texto
        printf("%hd %s", i, msg); // lo imprimo en pantalla
        i++;
    }
	
    printf("\n La informacion fue leida en %hd veces\n\n", i);
    fclose(archivo);
    return 0;
}
