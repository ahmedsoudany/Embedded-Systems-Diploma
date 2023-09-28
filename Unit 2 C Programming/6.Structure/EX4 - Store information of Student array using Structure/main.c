/*
 * main.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */

#include "stdio.h"

struct Sstudent
{
	char name[20];
	int roll_num;
	float grade;
};

int main()
{
	struct Sstudent x[10];
	int i;

	printf("Enter information of student: \r\n");

	for(i = 0 ; i < 10 ; i++)
	{

	x[i].roll_num = i + 1;
	printf("For roll number %d\n",i+1);

	printf("Enter name: ");
	fflush(stdin);fflush(stdout);
	scanf("%s",x[i].name);


	printf("Enter marks: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&x[i].grade);

	printf("\n");
	}
	printf("Displaying information: \r\n");

	for(i = 0 ; i < 10 ; i++)
	{
	printf("Information for roll number %d:\nName: %s\nMarks: %.2f\n",x[i].roll_num,x[i].name,x[i].grade);
	printf("\n");


	}
	return 0;
}
