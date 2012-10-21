#pragma once
#ifndef TCB_H
#define TCB_H

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

struct TCB_struct
{
	int tid;
	ucontext_t* context;
	State state;
	struct TCB_queue_struct* waiting_for_me;
};

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

typedef struct TCB_struct TCB;

typedef struct TCB_queue_node_struct TCB_queue_node;

typedef struct TCB_queue_struct TCB_queue;

TCB* 		Create_TCB(int tid, ucontext_t* context, State state);
int 		Update_TCB(TCB* t, ucontext_t* context, State state, TCB_queue* waiting_for_me);
int 		Block(TCB* blocking_thread, TCB* waiting_thread);
TCB_queue_node* Create_TCB_queue_node(int tid, ucontext_t* context, State state);
TCB_queue* 	Create_TCB_queue();
int 		Is_empty(TCB_queue* q);
int 		Enqueue(TCB_queue *q, TCB *t);
TCB* 		Dequeue(TCB_queue* q);
char* 		State_to_string(State state);
int 		Print_TCB_queue_node(TCB_queue_node* n);
int 		Print_TCB_queue(TCB_queue* q);
char* 		List_tids(TCB_queue* q);

#endif /*TCB_H*/
