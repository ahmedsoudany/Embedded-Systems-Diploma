/*
 * main.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"

int main()
{
    float num, product = 1;
	int i;

	for (i = 0; i < 4 ; i++)
	{
		printf("Enter num %d: ",i+1);
		fflush(stdout); fflush(stdin);
		scanf("%f",&num);
		if(num == 0)
			continue;
		product *= num;
	}

	printf("The product of the numbers is: %0.2f",product);

	return 0;
}
