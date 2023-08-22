/*
 * main.c
 *
 *  Created on: Aug 18, 2023
 *      Author: LEGION
 */


#include "stdio.h"
#include "math.h"
int calc_power(int base , int power_no);


int main()
{
	int base , power_no;
	printf("Enter base number: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&base);

	printf("Enter power number(positive integer): ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&power_no);

	printf("%d^%d = %d",base , power_no, calc_power(base,power_no));

	return 0;
}

int calc_power(int base , int power_no)
{
	if(power_no != 0)
	     return pow(base,power_no);
	else
		return 1;
}
