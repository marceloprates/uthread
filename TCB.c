#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum
{
	ready,
	running,
	blocked
} State;

typedef struct
{
	int tid;
	ucontext_t* context;
	State state;
} TCB;

struct TCB_queue_node_struct
{
	TCB* data;
	struct TCB_queue_node_struct* next;
};

typedef struct TCB_queue_node_struct TCB_queue_node;

typedef struct 
{
	TCB_queue_node* front;
	TCB_queue_node* rear;
} TCB_queue;

//

TCB* Create_TCB(int tid, /*ucontext_t* context,*/ State state)
{
	TCB* t = (TCB*)malloc(sizeof(TCB));

	t->tid = tid;
	t->state = state;

	return t;
}

TCB_queue_node* Create_TCB_queue_node(int tid, /*ucontext_t* context,*/ State state)
{
	TCB* t = Create_TCB(tid, /*context,*/ state);

	TCB_queue_node* n = (TCB_queue_node*)malloc(sizeof(TCB_queue_node));

	n->data = t;
	n->next = NULL;

	return n;
}

TCB_queue* Create_TCB_queue()
{
	return NULL;
}

int Is_empty(TCB_queue* q)
{
	return (q == NULL);
}

int Enqueue(TCB_queue* q, TCB* t)
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
			q->rear->next = new_element;
		}
		
		q->rear = new_element;

		return 1;
	}
}

int Dequeue(TCB_queue* q)
{
	if(Is_empty(q))
	{
		printf("\n * Queue already empty. Not dequeued * \n");
		return 0;
	}
	else if(&(q->front) == &(q->rear)) // queue has only one element
	{
		TCB_queue_node* element = q->front;

		free(element);

		q->front = NULL;
		q->rear = NULL;

		return 1;
	}
	else
	{
		TCB_queue_node* element = q->front;

		q->front = (q->front)->next;

		free(element);

		return 1;
	}
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

			printf("%d",tid);

			return 1;
		}

	}
}

int Print_TCB_queue(TCB_queue* q)
{
	TCB_queue_node* pointer = q->front;

	while(pointer != NULL)
	{
		int tid = (pointer->data)->tid;

		int print_ok = Print_TCB_queue_node(pointer);

		if(!print_ok) return 0;

		if(pointer->next != NULL)
		{
			printf(",");
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	TCB_queue* q = Create_TCB_queue();

	TCB* t1 = Create_TCB(1,ready);

	//Enqueue(q,t1);

	//Print_TCB_queue(q);
	
}
