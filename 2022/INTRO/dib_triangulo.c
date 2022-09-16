#include <stdio.h>

int main(void)
{
    int lineas;
    printf("Ingresa la cantidad de lineas que tiene la figura:  ");
    scanf("%d", &lineas);

    printf("\n");
    
    int i;
    for (i = 1; i <= lineas; i++)
    {
        int j;
        for (j = 0; j < i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    
    printf("\n");
    printf("\n");
    printf("\n");

    return 0;
}