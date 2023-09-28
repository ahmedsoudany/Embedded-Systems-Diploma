/*
 * main.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Ahmed melik alnasser said ahmed
 */


#include "stdio.h"

int main()
{
	int arr[15] , size , i;
	int *Parr = arr;

	printf("Input the number of elements to store in the array (max 15): ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&size);

	printf("Input %d number of elements in the array\n",size);

	for(i = 0 ; i < size ; i++,*Parr++)
	{
		printf("Elements - %d : ",i+1);
		fflush(stdin);fflush(stdout);
		scanf("%d",Parr);
	}

	*Parr--;

	printf("The elements of array in reverse order are :\n");

	for(i = size ; i > 0 ; i-- , *Parr--)
	{
		printf("Elements - %d : %d\n",i+1,*Parr);
	}
	return 0;
}

