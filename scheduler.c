#include "scheduler.h"

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
	TCB* thread = Create_TCB(tid++, starting_context, ready);

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
	Block_TCB(waited_for, thread);
	thread->state = blocked;
}

void Unblock(TCB* thread, TCB* waited_for)
{
	Unblock_TCB(waited_for, thread);
	thread->state = blocked;
}
