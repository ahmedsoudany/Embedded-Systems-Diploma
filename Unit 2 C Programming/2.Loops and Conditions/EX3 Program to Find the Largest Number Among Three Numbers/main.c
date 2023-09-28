/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */
#include "stdio.h"

int main()
{
	float a , b , c;

	printf("Enter three numbers: ");
	fflush(stdout);
	scanf("%f %f %f",&a,&b,&c);

	if(a>=b)
	{
		if(a>=c)
			printf("Largest number = %0.2f",a);
	}
	else if (c>=b)
		printf("Largest number = %0.2f",c);
	else
		printf("Largest number = %0.2f",b);

	return 0;
}

