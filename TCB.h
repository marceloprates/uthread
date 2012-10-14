#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	struct TCB_queue* waiting_for_me;
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

TCB* Create_TCB(int tid, ucontext_t* context, State state);
void Update_TCB(TCB* t, ucontext_t* context, State state, TCB_queue* waiting_for_me);
TCB_queue_node* Create_TCB_queue_node(int tid, ucontext_t* context, State state);
TCB_queue* Create_TCB_queue();
int Is_empty(TCB_queue* q);
int Enqueue(TCB_queue *q, TCB *t);
TCB* Dequeue(TCB_queue* q);
char* State_to_string(State state);
int Print_TCB_queue_node(TCB_queue_node* n);
int Print_TCB_queue(TCB_queue* q);
char* List_tids(TCB_queue* q);
