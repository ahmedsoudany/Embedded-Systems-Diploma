/*
 * main.c
 *
 *  Created on: Aug 17, 2023
 *      Author: LEGION
 */


#include "stdio.h"
#include "string.h"
int main()
{
	char str[30] , ch;
	int i,freq = 0;

	printf("Enter a string: ");
	fflush(stdout);fflush(stdin);
	scanf("%s",str);

	printf("Enter a character to find frequency: ");
	fflush(stdout);fflush(stdin);
	scanf("%c",&ch);


	for(i = 0 ; i < strlen(str) ; i++)
	{
		if(str[i] == ch)
		{
			++freq;
		}
	}

	printf("Frequency of %c = %d ",ch,freq);


	return 0;
}
