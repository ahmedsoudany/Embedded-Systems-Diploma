/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	float num;
	printf("Enter a number: ");
	fflush(stdout);
	scanf("%f",&num);

	if(num > 0)
		printf("%0.2f is positive.",num);
	else if (num < 0)
		printf("%0.2f is negative.",num);
	else
		printf("You entered zero.");

	return 0;
}
