#include<stdio.h>
#include<stdlib.h>

void convertir(char *letra);

int main()
{
    char letra = 'a';
    convertir(&letra);
	printf("%c",letra);
}

void convertir(char *letra)
{

    switch(*letra)
    {
        case 'A' ... 'Z':
                        *letra=*letra + 32;
                        break;
        case 'a' ... 'z':
                        *letra= *letra -32;
                        break;
    }
    return (*letra);
}