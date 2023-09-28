/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	float val_1,val_2;

	printf("Enter value of a: ");
	fflush(stdout);fflush(stdin);
	scanf("%f",&val_1);

	printf("Enter value of b: ");
	fflush(stdout);fflush(stdin);
	scanf("%f",&val_2);

	val_1 = val_1 + val_2;
	val_2 = val_1 - val_2;
	val_1 = val_1 - val_2;


	printf("After swapping, value of a = %.2f\n",val_1);
	printf("After swapping, value of b = %.1f\n",val_2);

	return 0;
}
