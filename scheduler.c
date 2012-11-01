#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"

TCB_list* all_threads;
TCB_queue* ready_threads;
TCB* running_thread;
int tid;

int Init_scheduler()
{
	ready_threads = TCB_queue_create();
	

	if(ready_threads == QUEUE_CREATION_ERROR)
	{
		return INIT_SCHEDULER_ERROR;
	}
	else
	{
		all_threads = TCB_list_create();

		if(all_threads == LIST_CREATION_ERROR)
		{
			return INIT_SCHEDULER_ERROR;
		}

		tid = 0;

		return NO_ERROR;
	}

	
}

int Create(ucontext_t* starting_context)
{
	if(tid > MAX_THREADS) // Maximum number of threads reached. We don't create the thread.
	{
		return MAX_THREADS_ERROR;
	}
	else
	{
		TCB* thread = TCB_create(tid++, starting_context, ready);

		TCB_list_add(all_threads, thread);

		return Ready(thread);
	}
}

int Ready(TCB* thread)
{
	thread->state = ready;

	int could_enqueue = Enqueue(ready_threads, thread);

	if(could_enqueue == ENQUEUE_ERROR)
	{
		return ENQUEUE_ERROR;
	}
	else
	{
		return thread->tid;
	}
}

TCB* Schedule()
{
	TCB* scheduled = Dequeue(ready_threads);

	if(scheduled == DEQUEUE_ERROR)
	{
		return DEQUEUE_ERROR;
	}
	else
	{
		running_thread = scheduled;
		scheduled->state = running;

		return scheduled;
	}
}

TCB* Running()
{
	return running_thread;
}

void Block(TCB* thread, TCB* waited_for)
{
	TCB_block(thread, waited_for);
}

void Unblock(TCB* thread, TCB* waited_for)
{
	TCB_unblock(thread, waited_for);

	Ready(thread);
}

void Unblock_waiting_for_me(TCB* thread)
{
	TCB_list_node* pointer = (thread->waiting_for_me)->front;

	while(pointer != NULL)
	{
		Unblock(pointer->data, thread);

		pointer = pointer->next;
	}
}

void Kill(TCB* thread)
{
	Unblock_waiting_for_me(thread);

	TCB_list_remove(all_threads, thread);

	free(thread->waiting_for_me);
	free(thread); // Frees pointer to thread that exited
}

TCB* Find_TCB(int tid)
{
	return TCB_list_get(all_threads, tid);
}

int No_threads_beside_main()
{
	return !TCB_list_is_empty(all_threads) && ((all_threads->rear)->data)->tid == 0;
}
