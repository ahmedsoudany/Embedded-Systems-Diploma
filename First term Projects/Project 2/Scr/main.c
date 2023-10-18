/*
 * main.c
 *
 *  Created on: Oct 17, 2023
 *      Author: Ahmed Melik Alnasser
 */

#include "SD.h"

int main()
{
	char text_temp[name_length];
	FIFO_BUF_st Student_queue;
	struct sinfo Student_buffer[Students_Number];
	ST_FIFO_init(&Student_queue,Student_buffer,Students_Number);
	DPRINTF("Welcome to the Student Management System\n");
	while(1){
		DPRINTF("\nChoose the task u want to perform\n");
		DPRINTF("1. Add the Student Details Manually\n");
		DPRINTF("2. Add the Student Details From Text File\n");
		DPRINTF("3. Find the Student Details by Roll Number\n");
		DPRINTF("4. Find the Student Details by First Name\n");
		DPRINTF("5. Find the Student Details by Course Id\n");
		DPRINTF("6. Find the Total number of Students\n");
		DPRINTF("7. Delete the Students Details by Roll Number\n");
		DPRINTF("8. Update the Students Details by Roll Number\n");
		DPRINTF("9. Show all information\n");
		DPRINTF("10. To Exit\n");
		DPRINTF("Enter you choice to perform the task: ");
		gets(text_temp);
		DPRINTF("\n ==================\n");
		switch(atoi(text_temp))
		{
		case 1:
			add_student_manually(&Student_queue);
			break;
		case 2:
			add_student_file(&Student_queue);
			break;
		case 3:
			find_student_by_roll(&Student_queue);
			break;
		case 4:
			find_student_by_fname(&Student_queue);
			break;
		case 5:
			find_student_by_course(&Student_queue);
			break;
		case 6:
			print_students_count(&Student_queue);
	        break;
		case 7:
			delete_student_by_roll(&Student_queue);
			break;
		case 8:
			update_student_by_roll(&Student_queue);
			break;
		case 9:
			show_student_info(&Student_queue);
			break;
		case 10:
			return 0;
		default:
			DPRINTF("\n Wrong option");
			break;
		}
	}
	return 0;
}
