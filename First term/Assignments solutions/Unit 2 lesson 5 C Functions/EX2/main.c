/*
 * main.c
 *
 *  Created on: Aug 18, 2023
 *      Author: LEGION
 */


#include "stdio.h"

int factorial(int x);


int main()
{
	int x = 3;
	printf("Enter an positive integer: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&x);
	printf("Factorial of %d = %d",x,factorial(x));

	return 0;
}

int factorial(int x)
{
	if(x == 0)
		return 1;

	return x*factorial(x-1);
}
