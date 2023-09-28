/*
 * main.c
 *
 *  Created on: Aug 17, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */


#include "stdio.h"

int main()
{
	int arr[10][10];
	int i ,j , r , c;

	printf("Enter rows and columns of the matrix: ");
	fflush(stdout); fflush(stdin);
	scanf("%d",&r);
	scanf("%d",&c);



	printf("Enter Elements of the matrix\n");

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("Enter elements a%d%d: ",i+1,j+1);
			fflush(stdout); fflush(stdin);
			scanf("%d",&arr[i][j]);

		}
	}


	printf("\n");
	printf("Entered matrix\n");

	for(i = 0; i < r; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("%d\t",arr[i][j]);
		}
		printf("\n");
	}
-
	printf("\n");
	printf("Transpose of matrix\n");

	for(i = 0; i < c; i++)
	{
		for(j = 0; j < r; j++)
		{
			if(i==j)
				printf("%d\t",arr[i][j]);
			else
				printf("%d\t",arr[j][i]);
		}
		printf("\n");
	}
	return 0;
}
