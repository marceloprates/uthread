#include "scheduler.h"

TCB_queue* ready_threads;
TCB* running_thread;
int tid;

void Init_scheduler()
{
	ready_threads = Create_TCB_queue();
	tid = 0;
}

int Create(ucontext_t* starting_context)
{
	TCB* thread = (TCB*)malloc(sizeof(TCB));

	thread->tid = tid++;
	thread->context = starting_context;
	thread->waiting_for_me = Create_TCB_queue();

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
