/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"

int main()
{
	char ch;

	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c",&ch);

	if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') )
		printf("%c is a alphabet.",ch);
	else
		printf("%c is not an alphabet",ch);

	return 0;
}
