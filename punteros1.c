#include<stdio.h>

int main()
{
    float A = -2.9876535;
    char B = 'X';
    char texto[]="Hola mundo\n";
    
    float *p1;
    char *p2;
    
    p1 = &A;
    p2 = &B;
    
    printf("\n Tamanio puntero a float: %hd \n", sizeof(p1)); // Tamaño de los punteros
    printf("Tamanio puntero a char: %hd \n\n", sizeof(p2));

    printf("Tamanio del float: %hd \n", sizeof(A)); //Tamaño de las variables
    printf("Tamanio del char: %hd \n", sizeof(B));
    printf("Tamanio del texto: %hd \n\n", sizeof(texto));
    
    printf("Contenido de lo apuntado por p1: %f y contenido del float %f \n", *p1, A); // Contenido de las variables
    printf("Contenido de lo apuntado por p2: %c y contenido del char %c \n\n", *p2, B);
    
    p2=texto;
    
    printf("Texto: %s",p2);
    
    return 0;
}