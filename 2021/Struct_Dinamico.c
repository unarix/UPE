#include <stdio.h>
#include <stdlib.h>

// Declaramos la estructura con sus atributos y la llamamos "alumno"
struct alumno
{
    char apellido[50]; // tipo char de 50 posiciones.
    char nombre[50];
    short cod_materia;
    short nota;
};

void cargarAlumno(struct alumno *alumnos, short tamanio);
void imprimirAlumnos(struct alumno *alumnos, short tamanio, short opcion);

int main(void)
{
    // Inicializo variables

    short i=0;
    short opcion = 0;
    short tamanio = 0; 
    
    struct alumno *alumnos = NULL;

    // *****************************
    // Inicia el flujo del programa
    // *****************************
    printf("Bienvenido al sistema *Cargar-Notas* \n"); 

    do
    {
        printf("Ingrese una opcion \n"); 
        printf("  1- Cargar alumnos \n"); 
        printf("  2- Listar Todos \n"); 
        printf("  3- Listar Aprobados \n"); 
        printf("  4- Listar desaprobados \n");
        printf("  5- Maximos, Minimos y Promedio \n");
        printf("  6- Salir \n");

        scanf("%hd", &opcion);

        switch (opcion)
        {
            case 1:
                tamanio = tamanio + 1;
                alumnos = realloc(alumnos, ( tamanio * sizeof(struct alumno)));

                if (alumnos == NULL)
                    printf("No hay suficiente memoria como para agregar un nuevo alumno.\n");
                else
                    cargarAlumno(alumnos,tamanio);

                break;
            case 2:
                imprimirAlumnos(alumnos, tamanio, 2);
                break;
            case 3:
                imprimirAlumnos(alumnos, tamanio, 3);
                break;
            case 4:
                imprimirAlumnos(alumnos, tamanio, 4);
            default:
                printf(" Error: %hd, no es una opcion correcta \n", opcion);
            
        }

    } while (opcion>0 && opcion<6);
    
    return(0);
}

void cargarAlumno(struct alumno *alumnos, short tamanio)
{
    // Ahora que estoy seguro, igualo mi vector al 
    printf("Carga de datos para el Alumno: \n");
    printf(" > Ingrese el nombre del alumno: ");
    scanf("%s", alumnos[tamanio-1].nombre);  
    fflush(stdin);
    printf(" > Ingrese el apellido del alumno: ");
    scanf("%s", alumnos[tamanio-1].apellido); 
    fflush(stdin);
    printf(" > Ingrese cod de materia: ");
    scanf("%hd", &alumnos[tamanio-1].cod_materia);
    printf(" > Ingrese su nota: ");
    scanf("%hd", &alumnos[tamanio-1].nota);
    printf(" \n"); 
}

void imprimirAlumnos(struct alumno *alumnos, short tamanio, short opcion)
{
    // Imprimimos el listado de las cajas que se cargaron:
    short desde=0;
    short hasta=0;

    if(opcion==3)
    {
        desde=4;
        hasta=10;
    }
    else if(opcion==4)
    {
        desde=0;
        hasta=4;
    }

    printf("*** Listado de alumnos: ***\n\n");

    for (int i=0; i<tamanio; i++)
    {
        if(alumnos[i].nota>desde && alumnos[i].nota<hasta)
        {
            printf(" > Nombre y apellido %s %s\n", alumnos[i].nombre, alumnos[i].apellido);
            printf("   Codigo de materia %hd \n", alumnos[i].cod_materia);
            printf("   Nota %hd \n", alumnos[i].nota);
            printf(" \n");
        }
    }
}
