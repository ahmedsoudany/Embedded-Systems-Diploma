/*
 * main.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */

#include "stdio.h"


int main()
{

	struct Sstudent
	{
		char name[20];
		int roll_num;
		float grade;
	};
	struct Sstudent x;

	printf("Enter information of student: \n");

	printf("Enter name: ");
	fflush(stdin);fflush(stdout);
	scanf("%s",x.name);

	printf("Enter roll number: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x.roll_num);

	printf("Enter marks: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&x.grade);

	printf("Displaying information: \n");
	printf("name: %s\nRoll: %d\nMarks: %.2f",x.name,x.roll_num,x.grade);

	return 0;
}
