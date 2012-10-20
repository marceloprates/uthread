#include "TCB_list.h"

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TCB_list* TCB_list_create()
{
	TCB_list* new_list = (TCB_list*)malloc(sizeof(TCB_list));

	if(new_list == NULL)
	{
		printf("\n * List not created. No memory avaliable * \n");
	
		return NULL;
	}
	else
	{
		new_list->front = NULL;
		new_list->rear = NULL;

		return new_list;
	}
}

int TCB_list_is_empty(TCB_list* tcb_list)
{
	return (tcb_list->front == NULL && tcb_list->rear == NULL);
}

int TCB_list_add(TCB_list* tcb_list, TCB* tcb)
{
	TCB_list_node* new_node = (TCB_list_node*)malloc(sizeof(TCB_list_node));

	if(new_node == NULL)
	{
		printf("\n * Thread %d not added. No memory avaliable * \n", tcb->tid);

		return 0;
	}
	else if(tcb_list->rear == NULL) // list is empty
	{
		new_node->data = tcb;
		tcb_list->rear = new_node;
		tcb_list->front = new_node;
		(tcb_list->rear)->next = NULL;

		return 1;
	}
	else
	{
		new_node->data = tcb;

		(tcb_list->rear)->next = new_node;
		new_node->previous = tcb_list->rear;

		tcb_list->rear = (tcb_list->rear)->next;

		return 1;
	}
}

TCB* TCB_list_remove(TCB_list* tcb_list, TCB* tcb)
{
	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		if(TCB_equals(pointer->data,tcb))
		{
			TCB_list_node* to_be_removed = pointer;

			if(pointer->previous == NULL) // first element is to be removed
			{
				tcb_list->front = (tcb_list->front)->next;

				return to_be_removed->data;
			}
			else
			{
				(pointer->previous)->next = pointer->next;

				pointer = pointer->next;

				return to_be_removed->data;
			}
		}
		else
		{
			pointer = pointer->next;
		}
	}

	return NULL;
}

int TCB_list_contains(TCB_list* tcb_list, TCB* tcb)
{
	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		if(TCB_equals(pointer->data, tcb))
		{
			return 1;
		}

		pointer = pointer->next;
	}

	return 0;
}

char* TCB_list_to_string(TCB_list* tcb_list)
{
	char* TCB_list_string = "";
	
	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		char* TCB_string = TCB_to_string(pointer->data);

		if(!TCB_string)
		{
			return NULL;
		}
		else
		{
			char* s = malloc(snprintf(NULL, 0, "%s %s", TCB_list_string, TCB_string) + 1);
			sprintf(s, "%s %s", TCB_list_string, TCB_string);

			TCB_list_string = s;
		}

		pointer = pointer->next;
	}

	return TCB_list_string;
}

int Print_TCB_list(TCB_list* tcb_list)
{
	char* tcb_list_string = TCB_list_to_string(tcb_list);

	if(tcb_list_string == NULL)
	{
		printf("\n * Not able to convert list to string. List not printed *\n");	
		
		return 0;
	}
	else
	{
		printf("%s",tcb_list_string);
		
		return 1;
	}
}

int main(int argc, char *argv[])
{
	TCB_list* l = TCB_list_create();

	TCB* t1 = Create_TCB(1,NULL,ready);
	TCB* t2 = Create_TCB(2,NULL,ready);
	TCB* t3 = Create_TCB(3,NULL,ready);
	TCB* t4 = Create_TCB(4,NULL,ready);
	
	printf("\nAdding thread %d to list...\n",t1->tid); TCB_list_add(l,t1); Print_TCB_list(l); printf("\n");
	printf("\nAdding thread %d to list...\n",t2->tid); TCB_list_add(l,t2); Print_TCB_list(l); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t2->tid); Block(t1,t2); Print_TCB_list(l); printf("\n");
	printf("\nAdding thread %d to list...\n", t3->tid); TCB_list_add(l,t3); Print_TCB_list(l); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t3->tid); Block(t1,t3); Print_TCB_list(l); printf("\n");
	printf("\nRemoving and saving content into TCB variable 't4'...\n"); t4 = TCB_list_remove(l,t1); Print_TCB_list(l); printf("\n");
	printf("\nAdding TCB variable 't4' A.K.A. thread %d to list...\n",t4->tid); TCB_list_add(l,t4); Print_TCB_list(l); printf("\n");
	printf("\nHugging Joel Carbonera...\n");
}
