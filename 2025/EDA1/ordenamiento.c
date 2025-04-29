// Ordenamiento

#include<stdio.h>

#define N 20
int main(void)
{
    short vector[N]= {12,6,4,18,9,1,7,13,2,10,3,14,19,20,16,5,11,15,8,17};
    //short indice[N];
    short i;
    short j;
    short aux;

    for(i=0;i<N-1;i++)
        for(j=i+1;j<N;j++)
            if(vector[i]>vector[j])
            {
                aux=vector[i];
                vector[i]=vector[j];
                vector[j]=aux;
            }

    printf("Vector ordenado\n");

    for(i=0;i<N;i++)
        printf("%7hd\n",vector[i]);
        
return 0;
}