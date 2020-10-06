#include <stdio.h>
#include <stdlib.h>
#include <time.h>

short genRandom();

int main()
{
    srand(time(NULL));

    int i=1;

    while(i<11)
    {
        printf("Valor %hd: %hd \n", i, genRandom());
        i++;
    }   

}

short genRandom()
{
    return rand() % (90 - 40 + 1) + 40 ;
    //return rand();
}
