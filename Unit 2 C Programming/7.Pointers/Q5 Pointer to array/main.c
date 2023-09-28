/*
 * main.c
 *
 *  Created on: Aug 25, 2023
 *      Author: Ahmed Melik Alnasser Said ahmed
 */


#include "stdio.h"
#include "string.h"
typedef struct
{
	char name[20];
	int Id;
}SEmplymentdata;



int main()
{
	SEmplymentdata x[] = {{"Alex", 1002}};
	SEmplymentdata *Pdata = x;


	printf("Employee Name: %s\nEmployeee ID: %d",Pdata->name,Pdata->Id);



}
