/*
 * main.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Ahmed Melik Alnasser Said Ahmed
 */
#include "stdio.h"

struct Sdistance
{
	int feet;
	float inch;
};

void add_distance(struct Sdistance x,struct Sdistance y);

int main()
{
	struct Sdistance dist1,dist2;

	printf("Enter information for first distance: \n");
	printf("Enter feet: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&dist1.feet);
	printf("Enter inch: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&dist1.inch);
	printf("Enter information for Second distance: \n");
	printf("Enter feet: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&dist2.feet);
	printf("Enter inch: ");
	fflush(stdin);fflush(stdout);
	scanf("%f",&dist2.inch);

	add_distance(dist1,dist2);
	return 0;
}

void add_distance(struct Sdistance x,struct Sdistance y)
{
	struct Sdistance z;

	z.feet = (x.feet+y.feet);
	z.inch =(x.inch+ y.inch);

	if(z.inch > 12)
	{
		z.inch = z.inch - 12;
		++z.feet;
	}

	printf("Sum of distances = %d' - %.1f\"",z.feet,z.inch);
}
