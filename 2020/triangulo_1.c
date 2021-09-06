#include <stdio.h>
int main(void)
{
	float a, b, c;
 
	printf("Ingrese el valor de a: ");
	scanf("%f", &a);
	printf("Ingrese el valor de b: ");
	scanf("%f", &b);
	printf("Ingrese el valor de c: ");
	scanf("%f", &c);
 
	if (a==b)
	{
		if(b==c)
			printf("El triangulo es equilátero");
		else
			printf("El triangulo es isósceles");
	}
	else
	{
		if(b==c)
			printf("El triangulo es isósceles");
		else
		{
			if(c==a)
				printf("El triangulo es isosceles");
			else 
				printf ("El triangulo es escaleno");
		}
	}
 
	return 0;
}