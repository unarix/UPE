#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Vamos a ver los ciclos, 
    // Algunos les dicen ciclos, otros bucles, otros iterativas... 
    // Basicamente son rutinas de codigo que se ejecutan una y otra vez hasta que determinada condicion se cumpla
    // el primero que vamos a ver es el while y se usa para repetir 
    // una determinada porcion de codigo mientras se cumpla determinada condicion

    // Por ejemplo, si queremos imprimir en pantalla los numeros de 1 al 5, como harian sin usar while? 

    printf("%d \n",1);
    printf("%d \n",2);
    printf("%d \n",3);
    printf("%d \n",4);
    printf("%d \n",5);

    //Vamos a debuguear este codigo para ver como se va ejecutando paso a paso y despues lo comparamos con el while

    // Como podemos hacer esto mismo con while? 
    short num=1;
    while(num<6)
    {
        printf("%hd \n",num);
        //num = num + 1; 
        num++; // Esto es un contador! despues veremos lo que son los acumuladores.
    }

    /* Hagamos un ejersicio:
    Escriba un programa que pida dos números enteros. El programa pedirá de nuevo
    el segundo número mientras no sea mayor que el primero. El programa terminará
    escribiendo los dos números.*/
    short primer_numero=0;
    short segundo_numero=0;

    printf("Ingrese el primer numero: ");
    scanf("%hd",&primer_numero);
    
    printf("Ingrese el segundo numero numero: ");
    scanf("%hd",&segundo_numero);
    
    while(segundo_numero <= primer_numero) // lo que esta dentro del while se tiene que ejecutar si el segundo numero no es mayor que el primero.
    {
        printf("El numero %hd es menor que %hd \n", primer_numero, segundo_numero);
        
        printf("Ingrese el segundo numero numero nuevamente"); // Dentro del ciclo, tengo que volver a pedir el segundo numero
        scanf("%hd",&segundo_numero);
    }

    printf("Fin del programa");

    
    // El proximo ciclo que vamos a ver es el DO WHILE
    // La diferencia del do while con el while es que: 
    // Siempre se realiza la primer ejecucion y luego se evalua la exprecion de si tiene que seguir iterando o no. 
    // osea... hace, mientras. 
    // Vamos a seguir con el ejemplo de la clase pasada y lo ereescribimos con un dowhile...
    // Repitamos el ejersicio anterior
    /* Escriba un programa que pida dos números enteros. El programa pedirá de nuevo
    el segundo número mientras sea menor que el primero. El programa terminará escribiendo los dos números.*/

    short primer_numero_do=0;
    short segundo_numero_do=0;
    printf("Ingrese el primer numero: ");
    scanf("%hd",&primer_numero_do);

    do
    {
        printf("Ingrese el segundo numero: ");
        scanf("%hd",&segundo_numero_do);

        printf("El primer numero es %hd, el segundo numero %hd \n", primer_numero_do, segundo_numero_do);
        
    } while (segundo_numero_do < primer_numero_do);
    
    // Hagamos un Menu: 
    // SI ingreso la opcion 0, el programa finaliza
    // SI ingreso la opcion 1, el programa imprime "Eleccion 1 es valida"
    // SI ingreso la opcion 2, el programa imprime "Eleccion 2 es valida"
    // SI ingreso cualquier otra opcion el programa no la toma como valida
    short opcion=0;
        
    do
    {
        printf("Ingrese una opcion: ");
        scanf("%hd",&opcion);

        switch(opcion)
        {
            case 0:
                printf("  -> Saliendo del programa \n");
                break;
            case 1:
                printf("  -> Opcion 1 valida \n");
                break;
            case 2:
                printf("  -> Opcion 2 valida \n");
                break;
            default:
                printf("  -> La opcion no es valida \n");
        }
        
    } while (opcion!=0);
    
    printf("Programa terminado \n\n\n");

    // Como seria esto mismo pero con un  while? se puede hacer? 
    // Deberia repetir el pedido del dato 2 veces
    
    printf("Ingrese una opcion: ");
    scanf("%hd",&opcion);

    while (opcion!=0)
    {    
        switch(opcion)
        {
            case 0:
                printf("  -> Saliendo del programa \n");
                break;
            case 1:
                printf("  -> Opcion 1 valida \n");
                break;
            case 2:
                printf("  -> Opcion 2 valida \n");
                break;
            default:
                printf("  -> La opcion no es valida \n");
        }

        printf("Ingrese una opcion: ");
        scanf("%hd",&opcion);
    }


    // Veamos el ultimo de los ciclos, el ciclo FOR
    // El ciclo for es igual a los anteriores, pero con la siguiente diferencias
    // Generalmente lo vas a usar cuando ya sabes la cantidad de cosas que tenes que hacer.
    // Usamos while cuando no sabemos cuanto dura el bucle, usamos for cuando si sabemos cuando dura el bucle, el for tambien se usa para recorrer los array.
    // Supongamos que nos piden sumar los numeros enteros del 1 al 20 con un lazo FOR
    short suma=0;
    for (short i = 1; i < 21; i++) // i++ es un contador
    {
        suma = suma + i; // Suma es un ACUMULADOR
        printf("La suma da: %hd \n",suma);
    }
    
    printf("Fin! \n");


    // Hagamos esto mismo en conjunto sumando lo que aprendimos la semana anterior IF
    // Ingrese dos numeros y registre si el primero es mas grande que el segundo
    // Repetir la accion 10 veces
    short primero = 0;
    short segundo = 0;
    for(short i=0; i<10; i++)
    {
        printf("\n");
        printf("Ingrese el primero : ");
        scanf("%hd",&primero);
        
        printf("Ingrese el segundo : ");
        scanf("%hd",&segundo);
        
        if(primero > segundo)
            printf("El primero es mas grande \n");
        else
            printf("El segundo es mas grande \n");
    }

    return 0;
}
