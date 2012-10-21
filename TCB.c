#include "TCB.h"

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TCB* Create_TCB(int tid, ucontext_t* context, State state)
{
	TCB* t = (TCB*)malloc(sizeof(TCB));

	if(t == NULL)
	{
		printf("\n* Thread not created. No memory avaliable *\n");

		return NULL;
	}
	else
	{
		t->tid = tid;
		t->context = context;
		t->state = state;
		t->waiting_for_me = TCB_list_create();

		return t;
	}
}

int Update_TCB(TCB* t, ucontext_t* context, State state, TCB_list* waiting_for_me)
{

	if(t == NULL)
	{
		printf("\n * Thread not updated. Thread was empty * \n");

		return 0;
	}
	else
	{
		t->context = context;
		t->state = state;
		t->waiting_for_me = waiting_for_me;
		
		return 1;
	}
}

int TCB_equals(TCB* t1, TCB* t2)
{
	return (t1->tid == t2->tid);
}

int Block(TCB* blocking_thread, TCB* waiting_thread)
{
	if(blocking_thread == NULL)
	{
		printf(" * 'Waiting for me' queue not updated. Blocking thread was empty * \n");

		return 0;
	}
	else if(waiting_thread == NULL)
	{
		printf(" * 'Waiting for me' queue not updated. Waiting thread was empty * \n");

		return 0;
	}
	else
	{
		TCB_list_add(blocking_thread->waiting_for_me, waiting_thread);

		return 1;
	}
}

int Unblock(TCB* blocking_thread, TCB* waiting_thread)
{
	if(blocking_thread == NULL)
	{
		printf(" * 'Waiting for me' queue not updated. Blocking thread was empty * \n");

		return 0;
	}
	else if(waiting_thread == NULL)
	{
		printf(" * 'Waiting for me' queue not updated. Waiting thread was empty * \n");

		return 0;
	}
	else
	{
		TCB_list_remove(blocking_thread->waiting_for_me, waiting_thread);

		return 1;
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

char* TCB_to_string(TCB* tcb)
{
	if(tcb == NULL)
	{
		printf("\n * TCB was empty. Conversion to string failed * \n");

		return NULL;
	}
	else
	{
		int tid = tcb->tid;
		State state = tcb->state;
		TCB_list* waiting_for_me = tcb->waiting_for_me;

		char* waiting_for_me_string = TCB_list_enumerate_tids(waiting_for_me);
		
		char* format = "Thread: %d, State: %s, Waiting for me: %s\n";

		// memory allocation and string concatenation
		char* TCB_string = malloc(snprintf(NULL, 0, format, tid, State_to_string(state), waiting_for_me_string) + 1);
		sprintf(TCB_string, format, tid, State_to_string(state), waiting_for_me_string);
		
		return TCB_string;
	}
}
