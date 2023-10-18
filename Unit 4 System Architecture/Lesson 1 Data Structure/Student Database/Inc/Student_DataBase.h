/*
 * Student_DataBase.h
 *
 *  Created on: Oct 10, 2023
 *      Author: LEGION
 */

#ifndef STUDENT_DATABASE_H_
#define STUDENT_DATABASE_H_

#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "string.h"

#define DPRINTF(...) {fflush(stdout);\
					  fflush(stdin); \
					  printf(__VA_ARGS__);\
					  fflush(stdout);\
					  fflush(stdin);}

#define name_lenght 30

struct Sdata
{
	int ID;
	char name[name_lenght];
	float height;
};

struct SStudent
{
	struct Sdata Studnet;
	struct SStudent *PNextStudent;
};

void AddStudent();
int Delete_Student();
void View_Student();
void DeleteAll();
void fill_the_record(struct SStudent* new_student);
void GetNth(unsigned char index);
void Get_Nodes_Number();
int Get_count();
void Nth_end(unsigned char index);
int middle_linkedlist();
int detectloop();
void Reverse_linkedlist();

#endif /* STUDENT_DATABASE_H_ */
