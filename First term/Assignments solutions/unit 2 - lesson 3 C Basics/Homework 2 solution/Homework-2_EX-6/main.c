/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	unsigned int num;
	int i, sum = 0;

	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%d",&num);

	for(i = 0 ; i <= num ; i++)
	{

		sum += i;
	}
	printf("Sum = %d",sum);

	return 0;
}
