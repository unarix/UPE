#include <stdio.h>
#include <string.h>
#define TAM 100

int main()
{
char texto1[TAM];
char texto2[TAM];
short vocales=0;
short m=0;

printf("introduzca el texto N1:\n");
	fgets(texto1,sizeof(texto1),stdin);
printf("introduzca el texto N2:\n");
	fgets(texto2,sizeof(texto2),stdin);
printf("\nEl texto1 es: %s Y ",texto1);
printf("El texto2 es: %s",texto2);

printf("\n***********************************************\n");
//CANTIDAD DE CARACTERES SIN EL NULL
printf("El texto1 tiene %d caracteres y ",strlen(texto1));
printf("El texto2 tiene %d caracteres. ",strlen(texto2));
printf("\n***********************************************\n");
//CANTIDAD DE VOCALES
for(short i=0;i<TAM;i++)
{
	if(texto1[i]=='a'||texto1[i]=='e'||texto1[i]=='i'||texto1[i]=='o'||texto1[i]=='u'||texto1[i]=='A'||texto1[i]=='E'||texto1[i]=='I'||texto1[i]=='O'||texto1[i]=='U')
		{
        vocales++;
        }
}
printf("El texto1 posee %hd vocal/es.",vocales);
printf("\n***********************************************\n");

//CUANTAS 'M' Y 'm' TIENEN LOS TEXTOS
for(short i=0;i<TAM;i++)
{
	if(texto2[i]=='m'||texto2[i]=='M')
		{
        m++;
        }
}
printf("El texto2 posee %hd de M/m.",m);
printf("\n***********************************************\n");
//SON IGUALES O DISTINTOS AMBOS TEXTOS
if(strcmp(texto1,texto2)==0){
	printf("\nLos textos son iguales!");
}else{
	printf("\nLos textos son distintos!");
}
printf("\n***********************************************\n");
	
return 0;
}