/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	float val_1 = 25,val_2= 56;
	float *a , *b;

	//printf("Enter value of a: ");
	//fflush(stdout);fflush(stdin);
	//scanf("%f",&val_1);

	//printf("Enter value of b: ");
	//fflush(stdout);fflush(stdin);
	//scanf("%f",&val_2);

	a = &val_2;
	b = &val_1;

	val_1 = *a;
	val_2 = *b;

	printf("After swapping, value of a = %0.2f\n",val_1);
	printf("After swapping, value of b = %0.1f",val_2);

	return 0;
}