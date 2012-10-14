#include "TCB.h"

TCB_queue* ready;

void Init_scheduler()
{
	ready = Create_TCB_queue();
}

void Ready(TCB* thread)
{
	Enqueue(ready, thread);
}

TCB* Schedule()
{
	return Dequeue(ready);
}

TCB* Block(TCB* thread, TCB* waited_for)
{
	Enqueue(waited_for->waiting, thread);

	return Dequeue(ready);
}
