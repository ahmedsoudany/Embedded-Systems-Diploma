/*
 * main.c
 *
 *  Created on: Oct 10, 2023
 *      Author: LEGION
 */


#include "Student_Database.h"



int main()
{
	char temp_text[40];
	unsigned char index;

	while (1)
	{
		DPRINTF("\n ======================");
		DPRINTF("\n\t Choose one of the following options");
		DPRINTF("\n 1. Add_Student  ");
		DPRINTF("\n 2. Delete_Student  ");
		DPRINTF("\n 3. View_Students  ");
		DPRINTF("\n 4. DeleteAll  ");
		DPRINTF("\n 5. Get nth of linked list");
		DPRINTF("\n 6. Find length of linked list");
		DPRINTF("\n 7. Get nth of linked list from end of the list");
		DPRINTF("\n 8. Find the middle of the Linked list");
		DPRINTF("\n 9. Detect loop in linked list");
		DPRINTF("\n 10. Reverse linked list");
		DPRINTF("\n ENTER OPTION NUMBER: ");


		gets(temp_text);

		DPRINTF("\n ====================== \n");
		switch(atoi(temp_text))
		{
		case 1:
			AddStudent();
			break;
		case 2:
			Delete_Student();
			break;
		case 3:
			View_Student();
			break;
		case 4:
			DeleteAll();
			break;
		case 5:
			DPRINTF("Enter number of index: ",index);
			scanf("%d",&index);
			GetNth(index);
			break;
		case 6:
			Get_Nodes_Number();
			break;
		case 7:
			DPRINTF("Enter number of index: ",index);
			scanf("%d",&index);
			Nth_end(index);
			break;
		case 8:
			middle_linkedlist();
			break;
		case 9:
			detectloop();
			break;
		case 10:
			Reverse_linkedlist();
			break;
		default:
			DPRINTF("\n Wrong option");
			break;
		}

	}
	return 0;
}
