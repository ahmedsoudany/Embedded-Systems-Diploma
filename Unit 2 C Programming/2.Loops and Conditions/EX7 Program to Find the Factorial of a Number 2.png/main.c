/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */



#include "stdio.h"
int main()
{
	int num , i , fac = 1;

	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%d",&num);

	if(num>0)
	{
		for(i = 1 ; i <= num ; i++)

			fac*=i;

		printf("Factorial = %d",fac);
	}

	else
		printf("Error!!! Factorial of negative number doesn't exist");

	return 0;
}
