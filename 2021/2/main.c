// Universidad Provincial de Ezeiza UPE, Tecnicatura Universitaria en Desarrollo de Software
// Baus Javier Angel, 33.911.536, Sabado 20 de Noviembre 2021.


// ESTA RESUELTO PERFECTO
// Que es un struct? 
// porque no hicieron un menu? como lo hubiesen hecho? 
// porque no hicieron funciones? que es una funcion? que parte de este codigo podriamos hacerlo en una funcion? 
// Que tiene que tener declarada una funcion si o si? esta al principio del codigo. 
// Como retorno mas de un dato en una funcion? 
// QUE ES CASTEAR?
// QUE DIFERENCIA HAY ENTRE SECUENCIAL Y BINARIA?
// QUE OTRO METODO DE ORDENAMIENTO CONOCES ADEMAS DE BURBUJA?
// QUE ES STRCOPY
// QUE ES STRCOMPARE
// system("cls"); CONOCES ALGUNA MAS? 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maximo 450

//ESTRUCTURA

struct datos{
long dni;
char nomape[90];
char cargo[15];
short acomp;

};

//DECLARAMOS LAS FUNCIONES

short menu();
short validacion_pregunta (short);



int main(void)
{	//DECLARAMOS VARIABLES

struct datos vector[450];
short contador=0;
short opcion;
short pregunta;
short capacidad=450;
short bandera=0;
short personas=0;
short suma_acomp=0;
long dni=0;
short cant_acomp=0;
short porcentaje=0;
short contador_doc=0;
struct datos auxiliar;
long i,j;
short por_agregar=0;



do{
fflush(stdin);
printf("Seleccione una opcion para continuar:");
opcion=menu();
//SWITCH CASE PARA MENU
switch(opcion){
case 1: //PRIMER CASO INGRESAMOS DATOS
if(personas<=maximo)
do
    {fflush(stdin);
    printf("Ingrese DNI:");
    scanf("%ld",&vector[contador].dni);
    fflush(stdin);



    /*for(int i=0; i<contador; i++){                  //BUSCA EN LOS VECTORES QUE EL CODIGO NO ESTE YA INGRESADO
    while(vector[contador].dni==vector[i].dni||vector[contador].dni<0){
    printf("\nDNI exitente\nIngrese un nuevo DNI: ");     //EN EL CASO DE QUE YA ESTE INGRESADO PIDE UNO NUEVO OTORGANDOLE OTRO ESPACIO EN LA MEMORIA
    scanf("%ld", &vector[contador].dni);}}
    fflush(stdin); */

    printf("Ingrese Nombre y Apellido:");
    scanf("%[^\n]s",vector[contador].nomape);
    fflush(stdin);

    printf("Ingrese Cargo:\n Docente\n Administrativo\n Jerarquico\n Otros\n(Respetando mayusculas y minusculas)\n");
    scanf("%[^\n]s",vector[contador].cargo);

    if (strcmp(vector[contador].cargo,"Docente")==0)
    {contador_doc++;} //CUENTA LA CANTIDAD DE DOCENTES INGRESADOS Y LOS VA SUMANDO


    fflush(stdin);
    printf("Ingrese cantidad de acompañantes:");
    scanf("%hd",&vector[contador].acomp);
    fflush(stdin);

    por_agregar=personas+vector[contador].acomp+1; //CUENTA LAS PERSONAS YA AGREGADAS Y LAS SUMA A LAS QUE SE ESTAN POR AGREGAR
    //SI LA SUMA SUPERA LA CAPACIDAD DA MENSAJE DE ERROR E INVITA A CARGAR MENOS ACOMPAÑANTES
    if(por_agregar>capacidad)
    {printf("Capacidad superada.\n");
    fflush(stdin);
    printf("Ingrese menos acompañantes:\n");
    scanf("%hd",&vector[contador].acomp);
    fflush(stdin);
    suma_acomp=suma_acomp+vector[contador].acomp;
    }
    else //SI NO SUPERA LA CAPACIDAD CONTINUA CON LA CARGA NORMALMENTE
    suma_acomp=suma_acomp+vector[contador].acomp;
    contador++;

    personas=suma_acomp+contador;
    capacidad=maximo-personas;

    printf("La capacidad dispobible es: %hd\n\n",capacidad);

    printf("Desea ingresar otro invitado? Si=1 No=0: \n\n");
    scanf("%hd",&pregunta);

    validacion_pregunta(pregunta);

    if(personas>=maximo&&pregunta==1)

    printf("Recinto lleno\n\n");

else
    printf("Puede continuar\n\n");
    }while(personas<maximo&&pregunta==1);



    //IMPRIME LO CARGADO HASTA EL MOMENTO
    printf("La cantidad de invitados total es: %hd\n", contador);
    printf("La cantidad de Acompañantes es: %hd\n", suma_acomp);
    printf("La cantidad total de personas es: %hd\n", personas);
    printf("La capacidad dispobible es: %hd\n",capacidad);

    break;

    case 2: //CASO PARA BUSCAR EN LA LISTA DE INVITADOS
    printf("\n Consultar lista de invitados.\n\n");
    do{
    printf("\nIngrese DNI para buscar:\n");
    fflush(stdin);
    scanf("%ld", &dni);
    fflush(stdin);

    bandera=0;

    while(dni!=vector[bandera].dni&&bandera<contador)
    {
    bandera++;
    }if(vector[bandera].dni==dni)
    { printf("\nNombre y Apellido: %s\n\n ",vector[bandera].nomape);
    printf("Cantidad de personas que lo acompañan?\n"); //PIDE Y COMPARA LA CANTIDAD DE ACOMPAÑANTES PERMITIENDO O NEGANDO EL INGRESO
    scanf("%hd", &cant_acomp);
    if(cant_acomp>vector[bandera].acomp)
    {printf("No se permite el ingreso por superar la cantidad de acompañantes.\n\n");}
else
    printf("Ingreso permitido.\n\n");
    }


else
    printf("No se encontro el invitado.\n\n");




    printf("\nDesea cosultar otro DNI? Si=1 No=0:\n");
    scanf("%hd", &pregunta);
    fflush(stdin);
    }while(pregunta==1);
    break;
    case 3: //CASO PARA IMRPIMIR LISTA DE INVITADOS, Y ORDENARLOS POR DNI DESCENDENTE
    printf("\nVer lista de invitados.\n\n");
    for(int x=0; x<contador; x++)
    {
    printf("\nNombre y Apellido: %s\n DNI: %ld\n Cargo: %s\n\n" ,vector[x].nomape, vector[x].dni, vector[x].cargo);


    }
    //ORDENA POR DNI EN FORMA DESCENDENTE
    printf("Invitados ordenados por DNI.\n\n");
    for(i=0;i<contador-1;i++)
    for(j=i+1;j<contador;j++)
    if(vector[i].dni<vector[j].dni)
    {
    auxiliar=vector[i];
    vector[i]=vector[j];
    vector[j]=auxiliar;
    }
    for(i=0;i<contador;i++)
    printf("DNI: %ld\n Nombre y Apellido: %s\n Cargo: %s\n\n",vector[i].dni ,vector[i].nomape ,vector[i].cargo);
    printf("\nParticiparon del evento %hd Docentes.\n\n", contador_doc); //IMPRIME LA CANTIDAD DE DOCENTES QUE PARTICIPARON DEL EVENTO

    break;
    case 4:  //CASO PARA CALCULAR PORCENTAJE OCUPADO Y CANTIDAD DE ASISTENTES AL EVENTO


    porcentaje=(100*personas)/450;
    printf("Cantidad de personas que asistieron al evento: %hd \n\n" ,personas);
    printf("Porcentaje del recinto ocupado: %hd %%\n\n", porcentaje);

    break;
    }}while(opcion!=5);

    return 0;
    }

    //FUNCIONES
    //FUNCION MENU
    short menu(void)
    {
    short opcion;
    printf("\n\n------>MENU \n\n");
    printf("\n1. Ingresar personas a la lista de invitados.");
    printf("\n2. Consultar lista de invitados.");
    printf("\n3. Ver lista de invitados.");
    printf("\n4. Obtener estadisticas.");
    printf("\n5. Salir\n");
    fflush(stdin);

    printf("\nOpcion: ");
    scanf("%hd", &opcion);
    while(opcion<1||opcion>5)
    {
    printf("\n\nOpcion invalida\nIngrese una opcion correcta: ");
    fflush(stdin);
    scanf("%hd",&opcion);
    }
    return opcion;}



    short validacion_pregunta(short num){

    while(num!=1&&num!=0){
    printf("\nOpcion incorrecta! si=1 - no=0: ");
    scanf("%hd", &num);}

    return num;
    }


