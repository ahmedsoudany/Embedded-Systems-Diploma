/*
 * main.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"
#include "stdbool.h"
int main()
{
	int arr[30] ,arr_size, i , element_search;
	bool found = 0 ;
	printf("Enter number of elemnts: ");
	fflush(stdout);
	scanf("%d",&arr_size);

	printf("Enter elemnts: \n");
	fflush(stdout);
	for(i = 0 ; i < arr_size; i++)
	{
		scanf("%d",&arr[i]);
		printf("\t");
	}


	printf("\nEnter element to be searched: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&element_search);

	for(i = 0 ; i < arr_size ; i++)
	{
		if(arr[i] == element_search)
		{
			printf("Number found at loaction number %d",i+1);
			found = 1;
		}
		else
			continue;
	}

	if (found == 0)
		printf("Number not found");

}
