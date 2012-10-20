#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TCB_queue.h"

TCB_queue* TCB_queue_create()
{
	TCB_queue* new_queue = (TCB_queue*)malloc(sizeof(TCB_queue));

	if(new_queue == NULL)
	{
		printf("\n * Queue not created. No memory avaliable * \n");
	
		return NULL;
	}
	else
	{
		new_queue->front = NULL;
		new_queue->rear = NULL;
		return new_queue;
	}
}

int TCB_queue_is_empty(TCB_queue* q)
{
	return (q->front == NULL && q->rear == NULL);
}

int Enqueue(TCB_queue *q, TCB *t)
{
	TCB_queue_node* new_element = (TCB_queue_node*)malloc(sizeof(TCB_queue_node));

	if(new_element == NULL)
	{
		printf("\n * Thread nº %d not inserted. No memory avaliable * \n", t->tid);
		
		return 0;
	}
	else
	{
		new_element->data = t;
		new_element->next = NULL;
		
		if(TCB_queue_is_empty(q))
		{
			q->front = new_element;
			q->rear = new_element;
		}
		else
		{
			(q->rear)->next = (TCB_queue_node*)malloc(sizeof(TCB_queue_node));
			(q->rear)->next = new_element;
			q->rear = (q->rear)->next;
		}

		

		return 1;
	}
}

TCB* Dequeue(TCB_queue* tcb_queue)
{
	if(TCB_queue_is_empty(tcb_queue))
	{
		printf("\n * Queue already empty. Not dequeued * \n");
		return NULL;
	}
	else if(&(tcb_queue->front) == &(tcb_queue->rear)) // queue has only one element
	{
		TCB_queue_node* element = tcb_queue->front;
		
		tcb_queue->front = NULL;
		tcb_queue->rear = NULL;

		return element->data;
	}
	else
	{
		TCB_queue_node* element = tcb_queue->front;

		tcb_queue->front = (tcb_queue->front)->next;

		return element->data;
	}
}

char* TCB_queue_to_string(TCB_queue* tcb_queue)
{
	char* TCB_queue_string = "";
	
	TCB_queue_node* pointer = tcb_queue->front;

	while(pointer != NULL)
	{
		char* TCB_string = TCB_to_string(pointer->data);

		if(!TCB_string)
		{
			return NULL;
		}
		else
		{
			char* s = malloc(snprintf(NULL, 0, "%s %s", TCB_queue_string, TCB_string) + 1);
			sprintf(s, "%s %s", TCB_queue_string, TCB_string);

			TCB_queue_string = s;
		}

		pointer = pointer->next;
	}

	return TCB_queue_string;
}

int Print_TCB_queue(TCB_queue* tcb_queue)
{
	char* tcb_queue_string = TCB_queue_to_string(tcb_queue);

	if(tcb_queue_string == NULL)
	{
		printf("\n * Not able to convert queue to string. Queue not printed *\n");	
		
		return 0;
	}
	else
	{
		printf("%s",tcb_queue_string);
		
		return 1;
	}
}

int main(int argc, char *argv[])
{
	TCB_queue* q = TCB_queue_create();

	TCB* t1 = Create_TCB(1,NULL,ready);
	TCB* t2 = Create_TCB(2,NULL,ready);
	TCB* t3 = Create_TCB(3,NULL,ready);
	TCB* t4 = Create_TCB(4,NULL,ready);
	
	printf("\nEnqueuing thread %d...\n",t1->tid); Enqueue(q,t1); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing thread %d...\n",t2->tid); Enqueue(q,t2); Print_TCB_queue(q); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t2->tid); Block(t1,t2); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing thread %d...\n", t3->tid); Enqueue(q,t3); Print_TCB_queue(q); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t3->tid); Block(t1,t3); Print_TCB_queue(q); printf("\n");
	printf("\nDenqueuing and saving content into TCB variable 't4'...\n"); t4 = Dequeue(q); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing TCB variable 't4' A.K.A. thread %d...\n",t4->tid); Enqueue(q,t4); Print_TCB_queue(q); printf("\n");
	printf("\nHugging Joel Carbonera...\n");
}
