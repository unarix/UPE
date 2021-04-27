#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cantidad 4 // no se hacen edificios de mas de 20 departamentos

float valor_ganancia(unsigned long);
short terreno();

struct departamento
{
    char nombre[50]; // tipo char de 50 posiciones.
    short personas;
    short categoria;
    long valor;
};

int main()
{
    short opcionMenu;
    struct departamento deptos[cantidad];
    short finalizar=0;
    short continuar=1;
    short i=0;
    short contador_cuatro;
    short contador_seis;
    short contador_premium;
    short contador_standard;
    unsigned long costo=0;
    char nombre_buscar[50];
    short dato_mal=1;

    printf("Bienvenido al sistema *BOB Constructores* \n");
    
    while(finalizar!=1)
    {
        printf("Elija una opcion del menu: \n");
        printf(" 1- Presupuestar nuevo edificio \n");
        printf(" 2- Imprimir presupuesto \n");
        printf(" 3- Buscar familia \n");
        printf(" 4- Finalizar \n");
        scanf("%hd",&opcionMenu);

        switch (opcionMenu)
        {
        case 1:
            while (i<cantidad && continuar==1)
            {
                printf("Carga de datos para la familia %hd: \n",i+1);
                printf(" > Ingrese el nombre del dueno: ");
                scanf("%s", deptos[i].nombre);
                
                while(dato_mal==1)
                {
                    printf(" > Ingrese cantidad personas: ");
                    scanf("%hd", &deptos[i].personas);

                    if(deptos[i].personas == 4 || deptos[i].personas == 6)
                        dato_mal = 0;
                    else
                        printf("   --> La opcion no es correcta... 4 o 6 personas? \n");
                        
                }
                dato_mal=1;

                while(dato_mal==1)
                {
                    printf(" > Ingrese categoria: ");
                    scanf("%hd", &deptos[i].categoria);
                    
                    if(deptos[i].categoria == 1 || deptos[i].categoria == 2)
                        dato_mal = 0;
                    else
                        printf("   --> La opcion no es correcta... categoria 1 o 2? \n");
                }
                
                if(deptos[i].categoria=1)
                    contador_premium = contador_premium + 1;
                else
                    contador_standard = contador_standard + 1;
                

                if(deptos[i].personas==4)
                {
                    contador_cuatro = contador_cuatro + 1;
                    if (deptos[i].categoria==1)
                        deptos[i].valor = (200 * 5000);
                    else
                        deptos[i].valor =(200 * 7000);
                    
                    costo = costo + deptos[i].valor;
                }
                else
                {
                    contador_seis = contador_seis + 1;
                    if (deptos[i].categoria==1)
                        deptos[i].valor = (300 * 5000);
                    else
                        deptos[i].valor =(300 * 7000);
                    
                    costo = costo + deptos[i].valor;
                }


                printf(" > Ingrese 1 para continuar cargando familias? ");
                scanf("%hd", &continuar);
                printf(" \n"); // Salto de linea
                i = i+1; // Sumamos 1 al contador de posición del vector
            }
            break;
        case 2:

            printf(" ****************************************** \n");
            
            //Cant pisos
            if((contador_cuatro/2)>(contador_seis/2))
                printf("   - El edificio debe tener %hd pisos \n",contador_cuatro/2);
            else
                printf("   - El edificio debe tener %hd pisos \n",contador_seis/2);
            // Tamanio minimo del terreno
            printf("   - El terreno debe medir %hd metros cuadrados \n",terreno());
            // Costo de la construccion:
            printf("   - El costo de la construccion es: $%lu \n", costo);
            // Valor total de la construccion
            printf("   - El Valor con ganancia de la construccion es: $%f \n", valor_ganancia(costo));
            // Valor promedio
            printf("   - Valor promedio de cada departamento: $%f \n", valor_ganancia(costo) / contador_cuatro + contador_seis);
            // Cant Standard            
            printf("   - Cantidad de departamentos Standard %hd n",contador_standard);
            // Cant Premium
            printf("   - Cantidad de departamentos Premium %hd n",contador_premium);

            printf(" ****************************************** \n");
            break;
        case 3:
            printf(" > Ingrese el nombre del dueno a buscar: ");
            scanf("%s", nombre_buscar);

            for (i=0;i<cantidad;i++)
            {
                if(strcmp(nombre_buscar,deptos[i].nombre)==0)
                {
                    printf("   - Duenio: %s \n", deptos[i].nombre);
                    printf("   - Personas: %hd \n", deptos[i].personas);
                    printf("   - Categoria: %hd \n", deptos[i].categoria);
                    printf("   - Valor: $%f \n", deptos[i].valor * 1.2);
                }
                i = i++; 
            }
            break;
        case 4:
            finalizar = 1;
            break;
        default:
            break;
        }
    }
}

short terreno(){
    return 200*2+300*2;
};

float valor_ganancia(unsigned long costo)
{
    return costo * 1.2;
}