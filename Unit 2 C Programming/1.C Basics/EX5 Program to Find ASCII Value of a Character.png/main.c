/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"

int main()
{
	char ch;
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c",&ch);

	printf("%d",ch);

	return 0;
}

