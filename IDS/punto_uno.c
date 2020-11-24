#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>



 struct supyper{
    float superficie;
    float perimetro;
};

struct supyper persup (int radio);

int main()
{
    int radio=0;
    float superficieacum=0;
    float perimetroacum=0;
    int circulos=0;
    float promsuperficies=0;
    float promperimetro=0;
    float maxperimetro=0;
    struct supyper resultado;


    printf ("Ingrese el radio del circulo(ingrese 0 paraterminar): ");
    scanf ("%d",&radio);

    while(radio!=0){

     resultado=persup(radio);//llamo a la funcion
     circulos=circulos+1;
     perimetroacum=resultado.perimetro+perimetroacum;
     superficieacum=resultado.superficie+superficieacum;
     if(maxperimetro<resultado.perimetro)
     {
       maxperimetro=resultado.perimetro;
     }
    printf ("\nLa superficie del circulo es: %f\n",resultado.superficie);

    printf ("El perimetro del circulo es: %f\n",resultado.perimetro);


     printf ("\nIngrese el radio del circulo(ingrese 0 paraterminar): ");
     scanf ("%d",&radio);
    }
    if (circulos!=0){

        promperimetro= perimetroacum/circulos;
        promsuperficies= superficieacum/circulos;
    }



    printf ("\nLa cantidad de circulos fueron: %d \n",circulos);
    printf ("El promedio de superficies es: %f \n",promsuperficies);
    printf ("El promedio de perimetros es: %f \n",promperimetro);
    printf ("El mayor perimetro medido es: %f \n",maxperimetro);
    return 0;
}

struct supyper persup(int radio){

        float pi=3.1416;
        float perimetro=0;
        float superficie=0;
        struct supyper resultado;//Resultado supyper contiene Perimetro y superficie


        superficie=pi*(radio*radio);
        perimetro=2*(pi*radio);

        resultado.perimetro=perimetro;
        resultado.superficie=superficie;

        return resultado;
};