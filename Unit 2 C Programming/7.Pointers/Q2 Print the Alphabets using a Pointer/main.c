/*
 * main.c
 *
 *  Created on: Aug 25, 2023
 *      Author: LEGION
 */


#include "stdio.h"

int main()
{
	char ch = 'A';
    char *Pch = &ch;
    char flag = 1;

	for(; flag ; (*Pch+=1))
	{
		printf("%c \t",*Pch);
		if(*Pch == 'Z')
			flag = 0;
		if(*Pch == 'T')
			printf("\n");
	}
}
