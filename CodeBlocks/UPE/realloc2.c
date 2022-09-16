
#include <stdio.h>
#include <stdlib.h>


void mi_dinamic_gets(char ,short);

int mainss()
{
    char *texto=NULL;
    printf("Ingrese un texto= ");
    mi_dinamic_gets(&texto,30);

    if(texto!=NULL)
    {
        printf("\n\nTexto= %s\n",texto);
        printf("strlen(texto)= %hd\n",strlen(texto));
        printf("sizeof(texto)= %hd\n",sizeof(texto));
    }

    return 0;
}

void mi_dinamic_gets(char **texto, short cantidad)
{
    short indice=0;

    char letra;

    letra=getche();
    / el 13 es el ENTER en Windows */
    while(letra!=13 && indice < cantidad)
    {
        / para cada letra */
        (*texto)=(char *)realloc((*texto),(indice+1));
        if(*texto != NULL)
        {
            (*texto)[indice]=letra;
            indice++;
            letra=getche();
        }
        else
        {
            (*texto)=0;
        }

    }

    (*texto)=(char *)realloc((*texto),(indice+1)); / para el NULL */
    if(*texto != NULL)
        (*texto)[indice]=0; / NULL final en el string */
    else
        (*texto)=0; / devuelvo puntero NULL */
}
