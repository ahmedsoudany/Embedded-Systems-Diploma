/*
 * main.c
 *
 *  Created on: Aug 16, 2023
 *      Author: LEGION
 */


#include "stdio.h"

int main()
{
	float arr1[2][2] , arr2[2][2], sum = 0;
	int r , c;
	printf("EANTER THE ELEMENTS OF 1st matrix\n");
	for(r = 0 ; r < 2 ;r++)
	{
		for(c = 0 ; c < 2;c++)
		{
			printf("Enter a%d%d: ",r+1,c+1);
			fflush(stdout); fflush(stdin);
			scanf("%f",&arr1[r][c]);
		}
	}
	printf("EANTER THE ELEMENTS OF 2nd Matrix\n");
	for(r = 0 ; r < 2 ;r++)
	{

		for(c = 0 ; c < 2;c++)
		{
			printf("Enter b%d%d: ",r+1,c+1);
			fflush(stdout); fflush(stdin);
			scanf("%f",&arr2[r][c]);
		}
	}
	printf("\r\n");
	printf("Sum Of Matrix\n");
	for(r = 0 ; r < 2 ;r++)
	{
		for(c = 0 ; c < 2;c++)
		{
			sum = arr1[r][c] + arr2[r][c];
			printf("%0.1f\t",sum);
		}
		printf("\n");
	}

}
