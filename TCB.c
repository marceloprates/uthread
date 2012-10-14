#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TCB.h"

//

TCB* Create_TCB(int tid, ucontext_t* context, State state)
{
	TCB* t = (TCB*)malloc(sizeof(TCB));

	t->tid = tid;
	t->state = state;
	t->waiting_for_me = Create_TCB_queue();

	return t;
}

void Update_TCB(TCB* t, ucontext_t* context, State state, TCB_queue* waiting_for_me)
{
	t->context = context;
	t->state = state;
	t->waiting_for_me = waiting_for_me;
}

TCB_queue_node* Create_TCB_queue_node(int tid, ucontext_t* context, State state)
{
	TCB* t = Create_TCB(tid, context, state);

	TCB_queue_node* n = (TCB_queue_node*)malloc(sizeof(TCB_queue_node));

	n->data = t;
	n->next = NULL;

	return n;
}

TCB_queue* Create_TCB_queue()
{
	TCB_queue* new_queue = (TCB_queue*)malloc(sizeof(TCB_queue));

	new_queue->front = NULL;
	new_queue->rear = NULL;
}

int Is_empty(TCB_queue* q)
{
	return (q->front == NULL);
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
		
		if(Is_empty(q))
		{
			q->front = new_element;
		}
		else
		{
			q->rear->next = (TCB_queue_node*)malloc(sizeof(TCB_queue_node));
			q->rear->next = new_element;
		}

		q->rear = new_element;

		return 1;
	}
}

TCB* Dequeue(TCB_queue* q)
{
	if(Is_empty(q))
	{
		printf("\n * Queue already empty. Not dequeued * \n");
		return NULL;
	}
	else if(&(q->front) == &(q->rear)) // queue has only one element
	{
		TCB_queue_node* element = q->front;

		TCB* copy = (TCB*)malloc(sizeof(TCB));
		
		memcpy(copy,element->data,sizeof(element));

		free(element);

		q->front = NULL;
		q->rear = NULL;

		return copy;
	}
	else
	{
		TCB_queue_node* element = q->front;

		q->front = (q->front)->next;

		TCB* copy = (TCB*)malloc(sizeof(TCB));

		memcpy(copy,element->data,sizeof(element));

		free(element);

		return copy;
	}
}

char* State_to_string(State state)
{
	char* state_string;

	switch(state)
	{
		case ready:
			state_string = "ready";
			break;
		case running:
			state_string = "running";
			break;
		case blocked:
			state_string = "blocked";
			break;
	}

	return state_string;
}

int Print_TCB_queue_node(TCB_queue_node* n)
{
	if(n == NULL)
	{
		printf("\n * Node was empty. Not printed * \n");

		return 0;
	}
	else
	{
		TCB* t = n->data;

		if(t == NULL) 
		{
			printf("\n * Node had no data associated with it. Not printed * \n");
			
			return 0;
		}
		else
		{
			int tid = t->tid;
			State state = t->state;
			TCB_queue* waiting_for_me = t->waiting_for_me;

			printf("thread: %d, state: %s", tid, State_to_string(state));

			return 1;
		}

	}
}

int Print_TCB_queue(TCB_queue* q)
{
	TCB_queue_node* pointer = q->front;

	while(pointer != NULL)
	{
		int print_ok = Print_TCB_queue_node(pointer);

		if(!print_ok) return 0;

		printf("\n");

		pointer = pointer->next;
	}

	return 1;
}

char* List_tids(TCB_queue* q)
{
	char* tids_string;

	TCB_queue_node* pointer = q->front;

	while(pointer != NULL)
	{
		int tid = (pointer->data)->tid;

		char* buf;
		
		sprintf(buf,"%d",tid);

		strcat(tids_string,buf);

		if(pointer->next != NULL) strcat(tids_string,",");	

		pointer = pointer->next;
	}

	return tids_string;
}

int main(int argc, char *argv[])
{
	TCB_queue* q = Create_TCB_queue();

	TCB* t1 = Create_TCB(1,NULL,ready);
	TCB* t2 = Create_TCB(2,NULL,ready);
	TCB* t3 = Create_TCB(3,NULL,ready);

	Enqueue(q,t1); Print_TCB_queue(q); printf("\n");
	Enqueue(q,t2); Print_TCB_queue(q); printf("\n");
	Enqueue(q,t3); Print_TCB_queue(q); printf("\n");
	t3 = Dequeue(q); Print_TCB_queue(q); printf("\n");
	Enqueue(q,t3); Print_TCB_queue(q); printf("\n");
	
}
