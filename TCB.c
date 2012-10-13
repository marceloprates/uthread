
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
	struct TCB_queue_node* front;
	struct TCB_queue_node* rear;
} TCB_queue;

//

TCB_list Create_thread_queue()
{
	return NULL;
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
	queue
}
