/*
 * main.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "stdio.h"
#include "string.h"

int main()
{
	char str[20] , temp[20];
	int i , j;

	printf("Enter a string: ");
	fflush(stdout);fflush(stdin);
	gets(str);

	strcpy(temp,str);


	for(i = strlen(temp) - 1  , j = 0 ; i >= 0 ; --i , j++)
	{
		str[j] = temp [i] ;
	}

	printf("Reverse string is: %s",str);
}
