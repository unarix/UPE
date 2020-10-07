#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    short i=0;
    srand(time(NULL)); //<-- NO SACAR ESTO

    while(i<10)
    {
        printf("El valor generado es: %c\n", rand() % 127);
        i++;
    }

    // short A = 0;
    // short B = 0;
    // short C = 0;

    // A = rand () % (90-40+1) + 40;
    // B = rand () % (90-40+1) + 40;
    // C = rand () % (90-40+1) + 40;

    // //rand () % (HASTA-DESDE+1)

    // printf("El valor generado para A es: %hd\n", A);
    // printf("El valor generado para B es: %hd\n", B);
    // printf("El valor generado para C es: %hd\n", C);


}
