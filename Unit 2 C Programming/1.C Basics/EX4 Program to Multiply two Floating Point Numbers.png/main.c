/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	float num_1, num_2;
	printf("Enter two numbers: ");
	fflush(stdout);
	scanf("%f",&num_1);
	scanf("%f",&num_2);

	printf("Product: %f",num_1 * num_2);

	return 0;
}
