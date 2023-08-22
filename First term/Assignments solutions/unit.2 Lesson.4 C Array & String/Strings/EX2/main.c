/*
 * main.c
 *
 *  Created on: Aug 17, 2023
 *      Author: LEGION
 */


#include "stdio.h"

int main()
{
	char str[30];
	int i;

	printf("Enter a string: ");
	fflush(stdout);
	gets(str);

	for (i = 0  ; str[i]!= '\0'; i++);

	printf("The length of the string is: %d",i);
}
