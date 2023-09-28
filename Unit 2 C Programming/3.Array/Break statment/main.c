/*
 * main.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"


int main()
{
	int i,n;
	float num[n],avg = 0,sum = 0;

	printf("Enter the maximum of entered no.: ");
	fflush(stdout); fflush(stdin);
	scanf("%d",&n);
	for (i = 0 ; i < n  ; i++)
	{

		printf("Enter the %d number: ",i+1);
		fflush(stdout); fflush(stdin);
		scanf("%f",&num[i]);

		if(num[i] < 0)
		{
			n = i;
			break;
		}
		sum += num[i];
	}
	avg = sum / n;

	printf("The average of the maximum number is %0.2f",avg);

	return 0;
}
