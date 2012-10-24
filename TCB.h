#pragma once
#ifndef TCB_H
#define TCB_H

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TCB_list.h"

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

TCB* 	Create_TCB(int tid, ucontext_t* context, State state);
int 	Update_TCB(TCB* t, ucontext_t* context, State state, TCB_list* waiting_for_me);
int 	TCB_equals(TCB* t1, TCB* t2);
int 	Block_TCB(TCB* blocking_thread, TCB* waiting_thread);
int 	Unblock_TCB(TCB* blocking_thread, TCB* waiting_thread);
char* 	State_to_string(State state);
char* 	TCB_to_string(TCB* tcb);

#endif /*TCB_H*/
