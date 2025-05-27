// Bueno, que son los archivos binarios? (los que se almacenan en formato binario, vuelcan lo que esta en memoria RAM a Disco)
// Que tipos de archivos binarios conocen?
// Que es lo mas importante que tenemos que saber cuando manejamos los archivos binarios? El formato.

// Esto mismo, ahora se llama serializacion, volcar desde memoria a un archivo.
// DesSerializacion es levantar de un archivo e insertar en memoria.

#include <stdio.h>
#include <stdlib.h>
int main()
{
	// Vamos a crear un par de variables y un vector... esos los vamos a escribir en un archivo y luego los vamos a leer.
	short A= 1;
	short B= 2;
	short C[5]={3, 4, 5, 6, 7};
	//short i;
	FILE *archivo1; // no olvidar que esta variable es un puntero a nuestro archivo del tipo FILE!!!! 

	char nombrearchivo[]= "binario.bin"; // La extencion de este archivo puede ser la que nosotros querramos. 
	printf("\nCreamos un archivo de formato binario\n\n");
	archivo1=fopen(nombrearchivo, "wb"); // Que significa wb? 

	if(archivo1 != NULL) // Si se puede leer el archivo
	{
		fwrite(&A,sizeof(A), 1, archivo1); // ( La direccion de lo que quiero guardar, el tamano, cantidad de elementos, en donde )
		fwrite(&B,sizeof(B), 1, archivo1);
		fwrite(C,sizeof(C), 1, archivo1); // Para el vector no me hace falta el & ya que es un puntero.
		fclose(archivo1); // QUE PASA SI NO HAGO FCLOSE? 
	}
	else
		printf("\nNO se puede crear archivo\n");

	archivo1= fopen(nombrearchivo, "rb"); //QUE ES RB?
	if(archivo1 != NULL)
	{
		printf("\nLo abrimos para lectura en formato binario\n\n");
		while(!feof(archivo1)) // Si no llegue al final del archivo.
		{
            fread(&A,sizeof(A), 1, archivo1);
            fread(&B,sizeof(B), 1, archivo1);
            fread(C,sizeof(C), 1, archivo1);
        }
        fclose(archivo1); // RECORDAR QUE ESTO VA FUERA DEL WHILE, QUE PASARIA SI ESTA DENTRO?
        printf("A= %hd\n", A);
        printf("B= %hd\n", B);

        for(i=0;i<5;i++)
            printf("\nC[%hd]= %hd", i, C[i]);
	}
	else
		printf("\nNO se puede leer archivo\n");
	return 0;
}
