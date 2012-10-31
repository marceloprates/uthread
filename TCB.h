#pragma once
#ifndef TCB_H
#define TCB_H

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TCB_list.h"

#define NO_ERROR 0
#define OUT_OF_MEMORY_ERROR NULL
#define TCB_TO_STRING_ERROR NULL
#define TCB_IS_NULL_ERROR -1

typedef struct TCB_list_struct TCB_list; // forward declaration

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
	struct TCB_list_struct* waiting_for_me;
};

typedef struct TCB_struct TCB;

TCB* 	TCB_create(int tid, ucontext_t* context, State state);
int 	TCB_equals(TCB* t1, TCB* t2);
int 	TCB_block(TCB* waiting_thread, TCB* blocking_thread);
int 	TCB_unblock(TCB* waiting_thread, TCB* blocking_thread);
int 	TCB_is_blocked(TCB* thread);
char* 	State_to_string(State state);
char* 	TCB_to_string(TCB* tcb);

#endif /*TCB_H*/
