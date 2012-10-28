#include "scheduler.h"

TCB_list* all_threads;
TCB_queue* ready_threads;
TCB* running_thread;
int tid;

int Init_scheduler()
{
	ready_threads = TCB_queue_create();

	if(ready_threads == NULL) return -1;

	tid = 0;

	return 0;
}

int Create(ucontext_t* starting_context)
{
	TCB* thread = TCB_create(tid++, starting_context, ready);

	TCB_list_add(all_threads, thread);

	return Ready(thread);
}

int Ready(TCB* thread)
{
	int error;

	thread->state = ready;

	error = Enqueue(ready_threads, thread);

	if(error)
	{
		return error;
	}
	else
	{
		return thread->tid;
	}
}

TCB* Schedule()
{
	TCB* scheduled = Dequeue(ready_threads);
	running_thread = scheduled;
	scheduled->state = running;

	return scheduled;
}

TCB* Running()
{
	return running_thread;
}

void Block(TCB* thread, TCB* waited_for)
{
	TCB_Block(waited_for, thread);
	thread->state = blocked;
}

void Unblock(TCB* thread, TCB* waited_for)
{
	TCB_unblock(waited_for, thread);
	thread->state = blocked;
}

TCB* Find_TCB(int tid)
{
	return TCB_list_get(all_threads, tid);
}
