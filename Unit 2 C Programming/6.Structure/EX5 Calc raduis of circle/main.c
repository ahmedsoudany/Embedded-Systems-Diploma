/*
 * main.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"

#define __Pi__ 3.14
#define __Area__(r) (__Pi__*r*r)

int main()
{
	int raduis;
	printf("Enter the radius: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&raduis);

	printf("Area of circle %.2f",__Area__(raduis));

	return 0;
}
