#include <stdio.h>
#include <stdlib.h>


int main()
{
     char palabra[17];

     do
     {

        printf ("\n Ingrese una palabra: ");
        fgets(palabra,17,stdin);
        if(!((strcmp(palabra,"fin\n"))==0))
            {
            printf ("\n La palabra alrevez es: ");
            int largopalabra=strlen(palabra)-2;//el menos es xq se resta uno del strlen que cuenta el largo de la palabra y el otro es xq la palabra tiene un /n al final.
              do
                {
                    printf("%c",palabra[largopalabra]);
                    largopalabra--;
                }
            while (largopalabra>=0);
            }

     }
     while (!((strcmp(palabra,"fin\n"))==0));



     return 0;
}