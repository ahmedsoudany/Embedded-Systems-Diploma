/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{

	float a , b ;
	char ch;
	printf("Enter operation either + or - or * or divide : ");
	fflush(stdout);
	scanf("%c",&ch);

	printf("Enter two operands: ");
	fflush(stdout);fflush(stdin);
			scanf("%f",&a);
			scanf("%f",&b);
	switch(ch)
	{
	case '+':
	{
		printf("%0.1f + %0.1f = %0.1f",a,b,a+b);
	}
	break;
	case '-':
	{
		printf("%0.1f - %0.1f = %0.1f",a,b,a-b);
	}
	break;
	case '*':
	{
		printf("%0.1f * %0.1f = %0.1f",a,b,a*b);
	}
	break;

	case '/':
	{
		printf("%0.1f / %0.1f = %0.1f",a,b,a/b);
	}
	break;
	default:
	{
		printf("You entered a wrong operation");
	}
	break;
	}

	return 0;
}
