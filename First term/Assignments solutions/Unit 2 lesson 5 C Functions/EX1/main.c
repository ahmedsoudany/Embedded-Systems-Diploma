/*
 * main.c
 *
 *  Created on: Aug 18, 2023
 *      Author: LEGION
 */


#include "stdio.h"

void prime_Number(int x , int y);


int main()
{
	int x , y;
	printf("Enter two numbers(intervals): ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);
	scanf("%d",&y);
	prime_Number(x,y);
	return 0;
}

void prime_Number(int x , int y)
{
	int i;

	for(i = x ; i < y ;++i)
	{
		if(i%2 != 0 && i%3 != 0)
		printf("%d\t",i);
	}
}
