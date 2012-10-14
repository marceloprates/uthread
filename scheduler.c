#include "TCB.h"

TCB* Reschedule(TCB_queue* ready, TCB* thread)
{
	Enqueue(states->ready, thread);

	return Dequeue(states->ready);
}

TCB* Block(TCB_queue* ready, TCB* thread, TCB* waited_for)
{
	Enqueue(waited_for->waiting, thread);

	return Dequeue(states->ready);
}
