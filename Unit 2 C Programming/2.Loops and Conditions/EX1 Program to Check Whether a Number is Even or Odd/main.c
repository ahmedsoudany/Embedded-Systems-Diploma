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
	printf("Enter an integre you want to check: ");
	fflush(stdout);
	scanf("%d",&num);
	if(num%2 == 0)
		printf("%d is even.",num);
	else
		printf("%d is odd.",num);

	return 0;
}

