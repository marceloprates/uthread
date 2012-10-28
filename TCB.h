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

TCB* 	TCB_create(int tid, ucontext_t* context, State state);
int 	TCB_equals(TCB* t1, TCB* t2);
int 	TCB_block(TCB* blocking_thread, TCB* waiting_thread);
int 	TCB_unblock(TCB* blocking_thread, TCB* waiting_thread);
void 	TCB_unblock_waiting_for_me(TCB* thread);
int 	TCB_is_blocked(TCB* thread);
char* 	State_to_string(State state);
char* 	TCB_to_string(TCB* tcb);

#endif /*TCB_H*/
