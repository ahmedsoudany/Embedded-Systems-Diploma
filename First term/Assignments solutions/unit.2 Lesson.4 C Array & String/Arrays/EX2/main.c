/*
 * main.c
 *
 *  Created on: Aug 17, 2023
 *      Author: LEGION
 */


#include "stdio.h"

int main()
{
	float arr[100], sum;
	int i , arr_size;

	printf("Enter the numbers of data: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&arr_size);



	for(i = 0  , sum = 0 ; i < arr_size ; i++)
	{
		printf("%d. Enter number: ", i+1);
		fflush(stdout);fflush(stdin);
		scanf("%f",&arr[i]);
		sum += arr[i];
	}

	printf("Average = %.2f",sum/arr_size);
	return 0;
}
