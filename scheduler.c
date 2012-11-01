#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"

TCB_list* all_threads; // List containing all threads that haven't ended
TCB_queue* ready_threads; // Queue containing all threads on "ready" state
TCB* running_thread; // Pointer to the thread that is currently running
int tid_counter; // Counter for the next tid to be used when a thread is created
int thread_counter; // Counts how many threads exist at a given time

int Init_scheduler()
{
	ready_threads = TCB_queue_create();
	all_threads = TCB_list_create();
	
	if(ready_threads == QUEUE_CREATION_ERROR || all_threads == LIST_CREATION_ERROR)
	{
		return ERROR;
	}
	else
	{
		tid_counter = 0;
		thread_counter = 0;

		return NO_ERROR;
	}
}

int Create(ucontext_t* starting_context)
{

	if(tid_counter + 1 > MAX_THREADS) // Maximum number of threads reached. We don't create the thread.
	{
		return ERROR;
	}

	tid_counter++;
	thread_counter++;

	TCB* thread = TCB_create(tid_counter, starting_context, READY);

	if(thread == OUT_OF_MEMORY_ERROR)
	{
		return ERROR;
	}

	int result = TCB_list_add(all_threads, thread);

	if(result == LIST_ADD_ERROR)
	{
		return ERROR;
	}

	return Ready(thread); // Changes the thread state to "ready" and enqueues it
}

int Ready(TCB* thread)
{
	int could_enqueue = Enqueue(ready_threads, thread);

	if(could_enqueue == ENQUEUE_ERROR)
	{
		return ERROR;
	}
	else
	{
		thread->state = READY;

		return thread->tid;
	}
}

TCB* Schedule()
{
	TCB* scheduled = Dequeue(ready_threads);

	if(scheduled == DEQUEUE_ERROR)
	{
		return NULL;
	}
	else
	{
		running_thread = scheduled;
		scheduled->state = RUNNING;

		return scheduled;
	}
}

TCB* Running()
{
	return running_thread; // Retrieves the thread currently running
}

int Block(TCB* thread, TCB* waited_for)
{
	return TCB_block(thread, waited_for);
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

	TCB_list_remove(all_threads, thread); // Removes thread from list of current threads

	thread_counter--;
	free(thread->waiting_for_me); // Frees list of threads blocked by the thread that exited
	free(thread); // Frees pointer to thread that exited
}

TCB* Find_TCB(int tid)
{
	return TCB_list_get(all_threads, tid);
}

int No_threads_beside_main()
{
	return thread_counter == 1;
}
