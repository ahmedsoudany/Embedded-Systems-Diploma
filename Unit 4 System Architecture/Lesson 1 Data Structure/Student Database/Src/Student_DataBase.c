/*
 * Student_DataBase.c
 *
 *  Created on: Oct 10, 2023
 *      Author: LEGION
 */

#include "Student_DataBase.h"

struct SStudent* gpFirstStudent = NULL;


void fill_the_record(struct SStudent* new_student)
{
	char temp_text[name_lenght];

	DPRINTF("\nEnter student ID: ");
	gets(temp_text);
	new_student->Studnet.ID = atoi(temp_text);

	DPRINTF("\nEnter student name: ");
	gets(new_student->Studnet.name);

	DPRINTF("\nEnter student Height: ");
	gets(temp_text);
	new_student->Studnet.height = atof(temp_text);
}

void AddStudent()
{
	struct SStudent* plastStudent;
	struct SStudent* pNewStudent;

	if(!gpFirstStudent) //check if list is empty
	{
		//create first record
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));

		if(!pNewStudent)
		{
			printf("Can't create new student\n");
			return;
		}
		//Assign gpFirstStudent to the first student
		gpFirstStudent = pNewStudent;
	}
	else //if last contains records
	{
		//navigate till reach the last student
		plastStudent = gpFirstStudent;
		while(plastStudent->PNextStudent)
		{
			plastStudent = plastStudent->PNextStudent;
		}

		//Create new recode and assign the next pointer to it
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		plastStudent->PNextStudent = pNewStudent;
	}

	fill_the_record(pNewStudent);

	pNewStudent->PNextStudent = NULL;

}
int Delete_Student()
{
	char pDeletestudent[name_lenght];

	int selected_id;
	DPRINTF("Enter student ID to be deleted:");
	gets(pDeletestudent);
	selected_id = atoi(pDeletestudent);

	if(gpFirstStudent)
	{
		struct SStudent* pPreviousStudent = NULL;;
		struct SStudent* pSelectedStudent = gpFirstStudent;

		while(pSelectedStudent)
		{

			if((pSelectedStudent->Studnet.ID)==selected_id)
			{
				if(pPreviousStudent)
				{
					pPreviousStudent = pSelectedStudent->PNextStudent;
				}
				else
				{
					gpFirstStudent = pSelectedStudent->PNextStudent;
				}
				free(pSelectedStudent);
				return 1;

			}
			pPreviousStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->PNextStudent;
		}


	}
	else
		DPRINTF("Error: no elements assigned");
	return 0;
}

void View_Student()
{
	int count = 0;
	struct SStudent* pCurrentStudent = gpFirstStudent;
	if(gpFirstStudent)
	{
		while(pCurrentStudent)
		{
			DPRINTF("\n Recorded number: %d",count+1);
			DPRINTF("\n \t student ID: %d\n",pCurrentStudent->Studnet.ID);
			DPRINTF("\n \t student name: %s\n",pCurrentStudent->Studnet.name);
			DPRINTF("\n \t Enter student Height: %f\n",pCurrentStudent->Studnet.height);
			pCurrentStudent = pCurrentStudent->PNextStudent;
			count++;
		}
	}
	else
	{
		DPRINTF("\n Empty list");
	}
}


void DeleteAll()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;

	if(gpFirstStudent == NULL)
		DPRINTF("\n Empty List");
	while(pCurrentStudent)
	{
		struct SStudent* ptempStudent = pCurrentStudent;
		pCurrentStudent = pCurrentStudent->PNextStudent;
		free(ptempStudent);
	}
	gpFirstStudent = NULL;
}

//print values of linked list index
void GetNth(unsigned char index)
{
	struct SStudent *pStudent = gpFirstStudent;
	unsigned char count = 0;

	if(gpFirstStudent)
	{
		while(pStudent)
		{
			if(count == index)
			{
				DPRINTF("\n Recorded number: %d",index+1);
				DPRINTF("\n \t student ID: %d\n",pStudent->Studnet.ID);
				DPRINTF("\n \t student name: %s\n",pStudent->Studnet.name);
				DPRINTF("\n \t Enter student Height: %f\n",pStudent->Studnet.height);
				return;
			}

			count++;
			pStudent = pStudent->PNextStudent;

		}
	}
	else
		printf("Empty list");
}
//Get length of linked list(iterative function)
void Get_Nodes_Number()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	unsigned char count = 0;
	while(pCurrentStudent)
	{
		pCurrentStudent = pCurrentStudent->PNextStudent;
		count++;
	}
	printf("\n Length of nodes is: %d",count);
}
//Get length of linked list(Recursive function)
int Get_count()
{
	if(!gpFirstStudent)
	{
		return 0;
	}
	else
		return 1 + Get_count(gpFirstStudent->PNextStudent);
}

//Find nth node from end of linked list using two pointer
void Nth_end(unsigned char index)
{
	struct SStudent* pmain = gpFirstStudent;
	struct SStudent* pref = gpFirstStudent;
	int count = 0;
	while(count != index)
	{
		pref = pref->PNextStudent;
		count++;
	}

	while(pref->PNextStudent)
	{
		pmain = pmain->PNextStudent;
		pref = pref->PNextStudent;
	}

	DPRINTF("\n Recorded index %d from end zero-based",count+1);
	DPRINTF("\n \t student ID: %d\n",pmain->Studnet.ID);
	DPRINTF("\n \t student name: %s\n",pmain->Studnet.name);
	DPRINTF("\n \t Enter student Height: %f\n",pmain->Studnet.height);

}
//Find nth node from end of linked list using equation
int N_end(unsigned char n)
{
	unsigned char count = 0;
	struct SStudent* pmain = gpFirstStudent;
	while(pmain)
	{
		count++;
		pmain = pmain->PNextStudent;
	}
	return (count-n+1);
}

//Find the middle of the Linked list using counter
int middle_linkedlist()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	unsigned char count =0 , index = 0;
	if(gpFirstStudent)
	{
		while(pCurrentStudent->PNextStudent != NULL)
		{
			count++;
			pCurrentStudent = pCurrentStudent->PNextStudent;
		}
	}
	count = count/2;
	pCurrentStudent = gpFirstStudent;
	while(count)
	{
		pCurrentStudent = pCurrentStudent->PNextStudent;
		count--;
		index++;
	}

	DPRINTF("\n Recorded number: %d",index+1);
	DPRINTF("\n \t student ID: %d\n",pCurrentStudent->Studnet.ID);
	DPRINTF("\n \t student name: %s\n",pCurrentStudent->Studnet.name);
	DPRINTF("\n \t Enter student Height: %f\n",pCurrentStudent->Studnet.height);


}
//Find the middle of the Linked list using two pointers
void pmiddle_linkedlist()
{
	struct SStudent* pslow = gpFirstStudent;
	struct SStudent* pfast = gpFirstStudent;
	unsigned char index = 0;
	while(pfast->PNextStudent != NULL)
	{
		pslow = pslow->PNextStudent;
		pfast = pfast->PNextStudent->PNextStudent;
		index++;
	}

	DPRINTF("\n Recorded number: %d",index + 1);
	DPRINTF("\n \t student ID: %d\n",pslow->Studnet.ID);
	DPRINTF("\n \t student name: %s\n",pslow->Studnet.name);
	DPRINTF("\n \t Enter student Height: %f\n",pslow->Studnet.height);


}

int detectloop()
{
	struct SStudent *pslow = gpFirstStudent,*pfast = gpFirstStudent;

	while(pslow && pfast && pfast->PNextStudent)
	{
		pslow = pslow->PNextStudent;
		pfast = pfast->PNextStudent->PNextStudent;

		if(pslow == pfast)
		{
			DPRINTF("Loop founded");
			return 1;
		}
		else
		{
			DPRINTF("No Loop founded");
			return 0;
		}
	}

}
//Reverse a linked list
void Reverse_linkedlist()
{
	struct SStudent* pCurrentStudent  = gpFirstStudent;
	struct SStudent* pPreviousStudent = NULL;
	struct SStudent* pNextStudent 	  = NULL;

	if(gpFirstStudent)
	{
		while(pCurrentStudent)
		{
			pNextStudent = pCurrentStudent->PNextStudent;
			pCurrentStudent->PNextStudent = pPreviousStudent;
			pPreviousStudent = pCurrentStudent;
			pCurrentStudent = pNextStudent;
		}

		gpFirstStudent = pPreviousStudent;
	}

	else
	{
		DPRINTF("EMPTY LISY||\n");
	}
		return;
}
