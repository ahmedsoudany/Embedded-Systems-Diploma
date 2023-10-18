/*
 * SD.h
 *
 *  Created on: Oct 17, 2023
 *      Author: Ahmed Melik Alnasser
 */

#ifndef SD_H_
#define SD_H_

#include "stdio.h"
#include "string.h"

//Configurations for user
#define name_length 30
#define Courses_no 2
#define Students_Number 50


#define DPRINTF(...)   {fflush(stdout); \
						fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); \
						fflush(stdin);}

typedef unsigned int uint32t;

/*==============================typedef=======================================*/

struct sinfo
{
	char fname[name_length];
	char lname[name_length];
	int roll;
	float GPA;
	int cid[Courses_no];
};

typedef struct sinfo St;


typedef struct
{
	uint32t length;
	uint32t count;
	St	*base;
	St	*head;
	St	*tail;
}FIFO_BUF_st;

typedef enum
{
	FIFO_null,
	FIFO_no_error,
	FIFO_empty,
	FIFO_not_empty,
	FIFO_full,
	FIFO_not_full
}FIFO_STATUS_st;

/*==============================FIFO_APIs=======================================*/
FIFO_STATUS_st ST_FIFO_init(FIFO_BUF_st *fifo,St *buff,uint32t length);
FIFO_STATUS_st ST_FIFO_enqueue(FIFO_BUF_st *fifo,St item);
FIFO_STATUS_st ST_FIFO_dequeue(FIFO_BUF_st *fifo,St *item);
FIFO_STATUS_st ST_FIFO_FULL(FIFO_BUF_st* fifo);
FIFO_STATUS_st ST_FIFO_EMPTY(FIFO_BUF_st* fifo);
void add_student_file(FIFO_BUF_st *fifo);
void add_student_manually(FIFO_BUF_st *fifo);
void find_student_by_roll(FIFO_BUF_st *fifo);
void find_student_by_fname(FIFO_BUF_st *fifo);
void find_student_by_course(FIFO_BUF_st *fifo);
void print_students_count(FIFO_BUF_st *fifo);
void delete_student_by_roll(FIFO_BUF_st *fifo);
void update_student_by_roll(FIFO_BUF_st *fifo);
void show_student_info(FIFO_BUF_st *fifo);
void Print_St_Info(struct sinfo* pStudent);
struct sinfo *Search_by_Roll_no(FIFO_BUF_st *fifo,int roll);





#endif /* SD_H_ */
