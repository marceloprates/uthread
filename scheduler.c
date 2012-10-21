#include "scheduler.h"

TCB_queue* ready_threads;
TCB* running_thread;
int tid;

void Init_scheduler()
{
	ready_threads = TCB_queue_create();
	tid = 0;
}

int Create(ucontext_t* starting_context)
{
	TCB* thread = Create_TCB(tid++, starting_context, ready);

	return Ready(thread);
}

int Ready(TCB* thread)
{
	return Enqueue(ready_threads, thread);
}

TCB* Schedule()
{
	TCB* scheduled = Dequeue(ready_threads);
	running_thread = scheduled;

	return scheduled;
}

TCB* Running()
{
	return running_thread;
}
/*
TCB* Block(TCB* thread, TCB* waited_for)
{
	Enqueue(waited_for->waiting, thread);

	return Dequeue(ready);
}
*/
