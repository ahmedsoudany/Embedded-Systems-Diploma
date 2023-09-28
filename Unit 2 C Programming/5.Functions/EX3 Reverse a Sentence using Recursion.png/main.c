/*
 * main.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"


void reverse_sentence(void);

int main()
{
	printf("Enter a sentence: ");
	fflush(stdin);fflush(stdout);
    reverse_sentence();

	return 0;
}

void reverse_sentence(void)
{
	char c ;
	scanf("%c",&c);
	if( c != '\n')
	{
		reverse_sentence();
		printf("%c",c);
	}

}
