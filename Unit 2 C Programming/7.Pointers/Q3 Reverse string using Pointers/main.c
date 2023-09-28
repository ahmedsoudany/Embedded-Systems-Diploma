/*
 * main.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"
#include "string.h"

int main()
{

	char s[50];
	char *ptr = s;
	int i;

	printf("Input a string: ");
	fflush(stdin);fflush(stdout);
	scanf("%s",s);
	while(*ptr != '\0')
	{
		ptr++;
	}
	ptr--;
	printf("Reverse of the string is: ");
	for(i = 0 ; (*ptr)!=s[0]; i++,ptr--)
	{
		printf("%c",*ptr);
	}

	printf("%c",*ptr);
	ptr++;
	*ptr = '\0';
	return 0;

}
