
enum State
{
	ready,
	running,
	blocked
}

typedef struct
{
	int* tid;
	ucontext_t* context;
	State* state;
} TCB;

typedef struct
{
	TCB* data;
	TCB_queue_node* next;
} TCB_queue_node;

typedef struct 
{
	TCB_queue_node* front;
	TCB_queue_node* rear;
} TCB_queue;

//

TCB_list Create_thread_queue()
{
	return NULL;
}

int Is_empty(TCB_queue* q)
{
	return (q == NULL);
}

int Enqueue(TCB_queue* q, TCB* t)
{
	TCB_queue_node* new_element = (TCB_queue_node)malloc(sizeof(TCB_queue_node));

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
	else if(q.front == q.rear) // queue has only one element
	{
		TCB_queue_node* element = q->rear;

		free(element);

		q->front = NULL;
		q->rear = NULL;

		return 1;
	}
	else
	{
		TCB_queue_node* element = q->rear;
		
		free(element);

		q->rear = NULL;

		return 1;
	}
}

int Print(TCB_queue_node* n)
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
			int* tid = t->tid;

			if(tid == NULL)
			{
				printf("\n * Node TCB had no tid associated with it. Not printed * \n");

				return 0;
			}
			else
			{
				printf("%d",*tid);
				
				return 1;
			}
		}

	}
}

int Print(TCB_queue* q)
{
	TCB_queue_node* pointer = q->front;

	while(pointer != NULL)
	{
		int tid = (pointer->data)->tid;

		int print_ok = Print(pointer);

		if(!print_ok) return 0;

		if(pointer->next != NULL)
		{
			printf(",");
		}
	}

	return 1;
}
