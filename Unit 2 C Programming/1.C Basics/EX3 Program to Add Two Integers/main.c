/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	int num_1, num_2;
	printf("Enter two Integer: ");
	fflush(stdout);
	scanf("%d",&num_1);
	scanf("%d",&num_2);

	printf("Sum: %d",num_1 + num_2);

	return 0;
}
