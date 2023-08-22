/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	int num;
	printf("Enter a Integer: ");
	fflush(stdout);
	scanf("%d",&num);

	printf("You entered: %d",num);

	return 0;
}
