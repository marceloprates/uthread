#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TCB.h"

#define NO_ERROR 0
#define OUT_OF_MEMORY_ERROR NULL
#define ENQUEUE_ERROR -1
#define DEQUEUE_ERROR NULL
#define TCB_QUEUE_TO_STRING_ERROR NULL
#define PRINT_TCB_QUEUE_ERROR -1
#define QUEUE_CREATION_ERROR NULL


struct TCB_queue_node_struct
{
	struct TCB_struct* data;
	struct TCB_queue_node_struct* next;
};

struct TCB_queue_struct
{
	struct TCB_queue_node_struct* front;
	struct TCB_queue_node_struct* rear;
};

typedef struct TCB_queue_node_struct TCB_queue_node;

typedef struct TCB_queue_struct TCB_queue;

TCB_queue* TCB_queue_create();
int TCB_queue_is_empty(TCB_queue* tcb_list);
int Enqueue(TCB_queue* tcb_queue, TCB* tcb);
TCB* Dequeue(TCB_queue* tcb_queue);
int TCB_queue_contains(TCB_queue* tcb_queue, TCB* tcb);
char* TCB_queue_to_string(TCB_queue* tcb_queue);
int Print_TCB_queue(TCB_queue* tcb_queue);
