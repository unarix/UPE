#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct tipo1
{
    short entero;
    char nombre[50];
    float real;
};

short compara_universal(char *V1,short tam1, char *V2, short tam2);

int main(void)
{
    struct tipo1 mi_variable1[]= {{2,"Pepe",45.56},{6,"Pipo",76.76}};
    struct tipo1 mi_variable2[]= {{2,"Pepe",45.56},{6,"Pipo",76.76},{5,"Carlos",80.20}};
    short vector1[]={2,9,5,-3,7,1,19,22};
    short vector2[]={2,9,5,-3,7,1,19,22,25};
    short resultado;


    setlocale(LC_ALL, "spanish"); //Para escribir en castellano

    //resultado=compara_universal((char *)mi_variable1,sizeof(mi_variable1),(char *)mi_variable2,sizeof(mi_variable2));
    resultado=compara_universal((char *)vector1,sizeof(vector1),(char *)vector2,sizeof(vector2));
    switch(resultado)
    {
        case -1: printf("El tamaño de ambos es diferente!!\n");break;
        case 0: printf("El contenido es diferente!!\n");break;
        case 1: printf("El contenido es el mismo!!\n");break;
    }

    return 0;
}

short compara_universal(char *V1,short tam1, char *V2, short tam2)
{
    short indice=0;

    if(tam1!=tam2)//no son del mismo tamaño
    {
        return -1;
    }

    while(indice<tam1) //como ambos indices son iguales uso uno solo
    {
        if(V1[indice] != V2[indice])
            return 0;
        indice++;
    }
    return 1;
}
