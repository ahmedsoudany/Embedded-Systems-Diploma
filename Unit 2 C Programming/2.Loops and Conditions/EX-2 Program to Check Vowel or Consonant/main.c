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

	printf("Enter an alphabet: ");
	fflush(stdout);
	scanf("%c",&ch);

	if(ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' || ch == 'i' || ch == 'I' || ch == 'o' || ch == 'O' || ch == 'u' || ch == 'U')
		printf("%c is a vowel.",ch);
	else
		printf("%c is a consonant.",ch);

	return 0;

}

