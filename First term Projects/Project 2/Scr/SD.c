/*
 * SD.c
 *
 *  Created on: Oct 17, 2023
 *      Author: Ahmed Melik Alnasser
 */


#include "SD.h"
//APIs


FILE *pStudent_File;


FIFO_STATUS_st ST_FIFO_init(FIFO_BUF_st *fifo,St *buff,uint32t length)
{
	//check buff exists
	if(!buff|| !fifo || !length)
	{
		printf("Queuing initialization failed\n");
		return FIFO_null;
	}

	//FIFO initialization
	fifo->base = buff;
	fifo->head = fifo->base;
	fifo->tail = fifo->base;
	fifo->length = length;
	fifo->count = 0;

	if(fifo->base && fifo->head)
	{
		printf("Queuing initialization succeed\n");
		return FIFO_no_error;
	}



}

FIFO_STATUS_st ST_FIFO_enqueue(FIFO_BUF_st *fifo,St item)
{
	if(!fifo->base || !fifo->head || !fifo->base)
	{
		printf("FIFO enqueue failed\n");
		return FIFO_null;
	}

	if(ST_FIFO_FULL(fifo) == FIFO_full)
	{
		printf("FIFO enqueue failed, FIFO is full\n");
		return FIFO_full;
	}

	*(fifo->head) = item;

	//check if head reached the end of the queue
	if((fifo->head) == (fifo->base + fifo->length * sizeof(St)))
	{
		fifo->head = fifo->base;
	}
	else
	{
		fifo->head++;
	}

	fifo->count++;

	return FIFO_no_error;
}
FIFO_STATUS_st ST_FIFO_dequeue(FIFO_BUF_st *fifo,St *item)
{
	if(!fifo->base || !fifo->head || !fifo->base)
	{
		printf("FIFO dequeue failed\n");
		return FIFO_null;
	}

	if(ST_FIFO_EMPTY(fifo) == FIFO_empty)
	{
		printf("FIFO dequeue failed, FIFO is full\n");
		return FIFO_full;
	}

	*item = *(fifo->tail)  ;

	//check if head reached the end of the queue
	if((fifo->tail + 1) == (fifo->tail + fifo->length * sizeof(St)))
	{
		fifo->tail = fifo->base;
	}
	else
	{
		fifo->tail++;
	}

	fifo->count--;

	return FIFO_no_error;
}
FIFO_STATUS_st ST_FIFO_FULL(FIFO_BUF_st* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->base)
	{
		printf("FIFO full failed");
		return FIFO_null;
	}
	if(fifo->count == fifo->length)
	{
		return FIFO_full;
	}

	return FIFO_not_full;
}
FIFO_STATUS_st ST_FIFO_EMPTY(FIFO_BUF_st* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->base)
	{
		printf("FIFO empty failed");
		return FIFO_null;
	}
	if(fifo->count == 0)
	{
		return FIFO_empty;
	}

	return FIFO_not_empty;
}

struct sinfo *Search_by_Roll_no(FIFO_BUF_st *fifo,int roll)
{
	int i;
	//Starting from tail
	St *pStudent_Find_Roll = fifo->tail;

	//Loop in the queue
	for(i = 0 ; i < fifo->count ; i++)
	{
		if(roll == pStudent_Find_Roll->roll)
		{
			break;
		}
		//check if we reached the end of the queue
		if((pStudent_Find_Roll) == (fifo->base + fifo->length))
		{
			pStudent_Find_Roll = fifo->base;
		}
		else
		{
			//Increment to the next tail
			pStudent_Find_Roll++;
		}
	}

	//Check if did not find the roll student number
	if(i == fifo->count)
	{
		//Student not founded
		pStudent_Find_Roll = NULL;
	}

	//Return struct of the rolled number
	return pStudent_Find_Roll;
}
void Print_St_Info(struct sinfo* pStudent)
{
	int i;

	DPRINTF("\n======================\n");
	DPRINTF("\nStudent Details:");
	DPRINTF("\n Roll number: %d",pStudent->roll);
	DPRINTF("\n First name: %s",pStudent->fname);
	DPRINTF("\n Second name: %s",pStudent->lname);
	DPRINTF("\n GPA: %0.2f",pStudent->GPA);
	DPRINTF("\n Courses ID:");

	for(i=0 ; i < Courses_no;i++)
	{
		DPRINTF("\n Course %d ID: %d\n",i+1,pStudent->cid[i]);
	}

}
void add_student_manually(FIFO_BUF_st *fifo)
{

	St NewStudent;
	int i;

	DPRINTF("\nEnter Student roll number: ")
	scanf("%d",&NewStudent.roll);

	if(Search_by_Roll_no(fifo,NewStudent.roll))
	{
		//Print we fount the roll number exists
		DPRINTF("\nError: Roll number %d is taken",NewStudent.roll);
		return;
	}

	//Reading student data from file
	DPRINTF("\nEnter Student data");
	DPRINTF("\n First name: ");
	scanf("%s" , NewStudent.fname);
	DPRINTF("\n Second name: ");
	scanf("%s" , NewStudent.lname);
	DPRINTF("\n GPA: ");
	scanf("%f" , &NewStudent.GPA);




	DPRINTF("\n Courses ID:");
	//Reading course IDs
	for(i = 0 ; i < Courses_no ;i++)
	{
		DPRINTF("\n Course ID no: %d\n",i+1);
		scanf("%d",&NewStudent.cid[i]);
	}

	//Enqueue new student
	if((ST_FIFO_enqueue(fifo,NewStudent))== FIFO_no_error)
	{
		DPRINTF("\nStudent Details saved successfully!!!");
		return;
	}
	else
	{
		DPRINTF("\nError: Adding student failed!!!");
		return;
	}

}

void add_student_file(FIFO_BUF_st *fifo)
{

	St NewStudent;

	int i;

	//Open student file with reading option
	pStudent_File = fopen("student.txt","r");

	if(pStudent_File == NULL)
	{
		DPRINTF("\n Error: student.txt does not exists!!!");
		return;
	}

	//Reading students until end of file
	while(!feof(pStudent_File))
	{
		//Roll number of the student
		fscanf(pStudent_File, "%d" , &NewStudent.roll);

		//Check if roll number exist
		if(Search_by_Roll_no(fifo,NewStudent.roll) != NULL)
		{
			//Print we fount the roll number exists
			DPRINTF("\nError: Roll number %d is taken",NewStudent.roll);
			//ignore the rest of the line
			fscanf(pStudent_File,"%*[^n]");

			//Start over from next line in 	text file
			continue;
		}

		//Reading student data from file
		fscanf(pStudent_File, "%s" , NewStudent.fname);
		fscanf(pStudent_File, "%s" , NewStudent.lname);
		fscanf(pStudent_File, "%f" , &NewStudent.GPA);


		//Reading course IDs
		for(i=0 ; i < Courses_no;i++)
		{
			fscanf(pStudent_File, "%d" , &NewStudent.cid[i]);

		}

		//Enqueue new student
		if((ST_FIFO_enqueue(fifo,NewStudent))== FIFO_no_error)
		{
			DPRINTF("\nRoll number %d saved successfully!!!",NewStudent.roll);
		}
		else
		{
			DPRINTF("\nError: Adding student failed!!");
			return;
		}


	}

	DPRINTF("\n========Student details saved successfully!!!===========");

	//Close the file
	fclose(pStudent_File);

}
void find_student_by_roll(FIFO_BUF_st *fifo)
{

	St *NewStudent;
	int rolled_no;

	//check if queue exist
	if(ST_FIFO_EMPTY(fifo) == FIFO_empty || ST_FIFO_EMPTY(fifo) == FIFO_null)
	{
		DPRINTF("Finding rolled number failed");
		return;
	}

	DPRINTF("\n===============\n");
	DPRINTF("\nEnter Student roll number: ");
	scanf("%d",&rolled_no);

	NewStudent = Search_by_Roll_no(fifo,rolled_no);

	if(NewStudent)
	{
		Print_St_Info(NewStudent);
		return;
	}
	else
	{
		DPRINTF("\nStudent does not exist");
		return;
	}

}
void find_student_by_fname(FIFO_BUF_st *fifo)
{

	St *pStudent = fifo->tail;
	char f_name[name_length] , i;

	//check if queue exist
	if(ST_FIFO_EMPTY(fifo) == FIFO_empty || ST_FIFO_EMPTY(fifo) == FIFO_null)
	{
		DPRINTF("Finding rolled number failed");
		return;
	}

	DPRINTF("\n===============\n");
	DPRINTF("\nEnter Student first name: ");

	gets(f_name);

	//loop inside queue
	for(i = 0 ; i < fifo->count ; i++)
	{
		if(!(strcmp(f_name,pStudent->fname)))
		{
			Print_St_Info(pStudent);
			return;
		}

		else if((pStudent) == (fifo->base + fifo->length))
		{
			pStudent = fifo->base;
		}
		else
		{
			pStudent++;
		}

	}

	DPRINTF("\nError: %s Student is not found\n",f_name);
	return;

}
void find_student_by_course(FIFO_BUF_st *fifo)
{

	St *pStudent = fifo->tail;
	int ID ,i ,j, No_Enrolled_Student = 0;

	//check if queue exist
	if(ST_FIFO_EMPTY(fifo) == FIFO_empty || ST_FIFO_EMPTY(fifo) == FIFO_null)
	{
		DPRINTF("Finding rolled number failed");
		return;
	}

	//Get the id course
	DPRINTF("\nEnter Course ID: ");
	scanf("%d",&ID);

	//loop inside queue
	for(i = 0 ; i < fifo->count ; i++)
	{
		for(j = 0 ; j < Courses_no; j++ )
		{
			if(pStudent->cid[j] == ID)
			{
				Print_St_Info(pStudent);
				No_Enrolled_Student++;
				printf("\n");
				break;
			}
		}

		if((pStudent) == (fifo->base + fifo->length))
		{
			pStudent = fifo->base;
		}
		else
		{
			pStudent++;
		}

	}

	if(No_Enrolled_Student == 0)
	{
		printf("\nError: Course ID %d is not found\n", ID);
	}
	else
	{
		printf("\n[INFO] Total number of students enrolled: %d\n", No_Enrolled_Student);
	}
}

void delete_student_by_roll(FIFO_BUF_st *fifo)
{

	St *pStudent = fifo->base;
	int delete_roll , i ,flag = 0;

	//check if queue exist
	if(ST_FIFO_EMPTY(fifo) == FIFO_empty || ST_FIFO_EMPTY(fifo) == FIFO_null)
	{
		DPRINTF("\nFinding rolled number failed");
		return;
	}

	DPRINTF("\n===============\n");
	DPRINTF("\nEnter Student roll number: ");
	scanf("%d",&delete_roll);

	//Loop inside queue
	for(i = 0 ; i < fifo->count ; i++)
	{
		if(pStudent->roll == delete_roll)
		{
			//Deleting student
			//*pStudent = *(fifo->tail);
			ST_FIFO_dequeue(fifo,pStudent);
			flag = 1;
			break;
		}
		else
		{
			flag = 0;
		}
		pStudent++;
	}

	if(flag == 1)
	{
		DPRINTF("\nThe roll number is removed");
	}
	else
	{
		DPRINTF("\nError: The roll number %d not found",delete_roll);
	}
}

void update_student_by_roll(FIFO_BUF_st *fifo)
{
	St *pCurrentStudent, *pUdatedStudent;
	int i , rolled_no , update_option , New_rolled_no , flag = 0;

	//check if queue exist
	if(ST_FIFO_EMPTY(fifo) == FIFO_empty || ST_FIFO_EMPTY(fifo) == FIFO_null)
	{
		DPRINTF("Finding rolled number failed");
		return;
	}

	DPRINTF("\n Enter roll number: ");
	scanf("%d",&rolled_no);

	pUdatedStudent = Search_by_Roll_no(fifo,rolled_no);

	if(pUdatedStudent == NULL)
	{
		DPRINTF("Error: Rolled number not found");
		return;
	}
	else
	{
		DPRINTF("\n====Student data=======\n");
		Print_St_Info(pUdatedStudent);
	}

	DPRINTF("\nWhich data you want to change");
	DPRINTF("\n1. Roll number");
	DPRINTF("\n2. First name");
	DPRINTF("\n3. Last name");
	DPRINTF("\n4. GPA score");
	DPRINTF("\n5. The courseS ID");
	DPRINTF("\nEnter your option: ");

	scanf("%d",&update_option);

	switch(update_option)
	{
	case 1:
		DPRINTF("Enter the new roll number: ");
		scanf("%d",&New_rolled_no);

		pCurrentStudent = fifo->tail;
		// Loop inside the queue
		for (i = 0; i < fifo->count; ++i)
		{
			// Check if we find the the roll we search about to break
			if (pCurrentStudent->roll == New_rolled_no)
			{
				// Get out form for loop
				DPRINTF("\n[ERROR] This Roll Number %d is exist\n",New_rolled_no);

				// If we find a roll number match set flag
				flag = 1;
				break;
			}

			// Check if we reach the last item in the queue
			if((pCurrentStudent) == (fifo->base + fifo->length))
			{
				pCurrentStudent = fifo->base;
			}
			else
			{
				// Just go to the next tail :D
				pCurrentStudent++;
			}
		}

		// If the flag doesn't changed this mean that no roll number match
		if(flag == 0)
		{
			pUdatedStudent->roll = New_rolled_no;
			DPRINTF("\n[INFO] The Roll Number %d in updated successfully\n", New_rolled_no);
		}
	break;

	case 2:
		DPRINTF("Enter the new first name: ");
		scanf("%s", pUdatedStudent->fname);
		DPRINTF("\n[INFO] The First Name %s in updated successfully\n",pUdatedStudent->fname);
	break;

	case 3:
		DPRINTF("Enter the new last name: ");
		scanf("%s", pUdatedStudent->lname);
		DPRINTF("\n[INFO] The Last Name %s in updated successfully\n",pUdatedStudent->lname);
	break;

	case 4:
		DPRINTF("Enter the new GPA: ");
		scanf("%f", &pUdatedStudent->GPA);
		DPRINTF("\n[INFO] The GPA Score %0.1f in updated successfully\n", pUdatedStudent->GPA);
	break;

	case 5:
		DPRINTF("Enter the course number from %d to %d: ", 1, Courses_no);
		scanf("%d", &update_option);
		DPRINTF("Enter the new course id: ");
		scanf("%d", &pUdatedStudent->cid[update_option - 1]);
		DPRINTF("\n[INFO] The Course ID %d in updated successfully\n", pUdatedStudent->cid[update_option - 1]);
	break;

	default:
	break;

	}
}
void show_student_info(FIFO_BUF_st *fifo)
{

	St *pStudent;
	char i;
	//check if queue exist
	if(ST_FIFO_EMPTY(fifo) == FIFO_empty || ST_FIFO_EMPTY(fifo) == FIFO_null)
	{
		DPRINTF("ERROR: There are no student added\n");
		return;
	}

	DPRINTF("\nAll Students\n");

	pStudent = fifo->tail;
	//check if reached the last of queue
	for(i = 0 ; i < fifo->count; i++)
	{
		Print_St_Info(pStudent);

		if((pStudent) == (fifo->base + fifo->length))
		{
			pStudent = fifo->base;
		}
		else
		{
			pStudent++;
		}
	}

}
void print_students_count(FIFO_BUF_st *fifo)
{
	int count = fifo->count;
	int max_count = fifo->length;

	DPRINTF("\nYou can add up to %d students",max_count);
	DPRINTF("\nTotal number of students Added %d",count);
	DPRINTF("\nTotal number of students you can still Add %d",max_count - count);
}
