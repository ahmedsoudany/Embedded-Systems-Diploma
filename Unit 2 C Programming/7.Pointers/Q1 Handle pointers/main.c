/*
 * main.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Ahmed melik alnasser said ahmed
 */


#include "stdio.h"

int main()
{
	int m = 29;
	int *ab = NULL;

	printf("Address of m : %p\n",&m);
	printf("Value of m : %d\r\n",m);

	ab = &m;

	printf("Address of ab : %p\n",ab);
	printf("Value of ab : %d\r\n",*ab);

	m = 34;

	printf("Address of ab : %p\n",ab);
	printf("Value of ab : %d\r\n",*ab);

	*ab = 7;

	printf("Address of m : %p\n",&m);
	printf("Value of m : %d",m);

	return 0;
}




