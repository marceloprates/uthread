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
		t->state = state;
		t->waiting_for_me = Create_TCB_list();

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
		
		char* format = "Thread: %d, State: %s\n";

		char* TCB_string = malloc(snprintf(NULL, 0, format, tid, State_to_string(state)) + 1);
		sprintf(TCB_string, format, tid, State_to_string(state));
		
		return TCB_string;
	}
}

/*int main(int argc, char *argv[])
{
	
	TCB_queue* q = Create_TCB_queue();

	TCB* t1 = Create_TCB(1,NULL,ready);
	TCB* t2 = Create_TCB(2,NULL,ready);
	TCB* t3 = Create_TCB(3,NULL,ready);
	TCB* t4 = Create_TCB(4,NULL,ready);

	
	printf("\nEnqueuing thread %d...\n",t1->tid); Enqueue(q,t1); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing thread %d...\n",t2->tid); Enqueue(q,t2); Print_TCB_queue(q); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t2->tid); Block(t1,t2); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing thread %d...\n", t3->tid); Enqueue(q,t3); Print_TCB_queue(q); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t3->tid); Block(t1,t3); Print_TCB_queue(q); printf("\n");
	printf("\nDenqueuing and saving content into TCB variable 't4'...\n"); t4 = Dequeue(q); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing TCB variable 't4' A.K.A. thread %d...\n",t4->tid); Enqueue(q,t4); Print_TCB_queue(q); printf("\n");
	printf("\nHugging Joel Carbonera...\n");
}*/
