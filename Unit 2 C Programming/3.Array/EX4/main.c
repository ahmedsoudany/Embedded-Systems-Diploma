/*
 * main.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"

int main()
{
	int arr[20] ,arr_size, i , element , location ;

	printf("Enter no of elemnets: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&arr_size);

	printf("Enter elements: ");
	printf("\n");
	fflush(stdout);fflush(stdin);
	for(i = 0 ; i < arr_size; i++)
	{
		scanf("%d",&arr[i]);
	}


	printf("Enter element to be inserted: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&element);

	printf("Enter location: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&location);



	for(i = arr_size  ; i >= location;i--)
	{
		arr[i] = arr[i - 1];
	}
	arr_size++;
	arr[location] = element;

	for(i = 0 ; i < arr_size ; i++)
	{
		printf("%d ",arr[i]);
	}

	return 0;

}
