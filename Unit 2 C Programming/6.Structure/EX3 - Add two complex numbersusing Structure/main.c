/*
 * main.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */
#include "stdio.h"

struct Scomplex
{
	float real_num;
	float imag_num;
};

void add_distance(struct Scomplex x,struct Scomplex y);

int main()
{
	struct Scomplex complex_1,complex_2;

	printf("Enter 1st complex: \n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdin);fflush(stdout);

	scanf("%f",&complex_1.real_num);
	scanf("%f",&complex_1.imag_num);
	printf("Enter 2nd complex: \n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdin);fflush(stdout);

	scanf("%f",&complex_2.real_num);
	scanf("%f",&complex_2.imag_num);

	add_distance(complex_1,complex_2);
	return 0;
}

void add_distance(struct Scomplex x,struct Scomplex y)
{
	struct Scomplex sum;
	sum.real_num = (x.real_num+y.real_num);
	sum.imag_num =(x.imag_num+ y.imag_num);
	printf("Sum of distances = %.1f + %.1fi",sum.real_num,sum.imag_num);
}

