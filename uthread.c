#include "scheduler.h"
#include "dispatcher.h"
#include "contexts.h"

int Dispatch_next_thread()
{
	TCB* thread = Schedule();

	if(thread != NULL)
	{
		Dispatch(thread);
	}
	else
	{
		return 0; // Ready queue emptyied. All threads are now finished.
	}
}

void Change_current_thread()
{
	Ready(Running()); // Running thread is 'stopped', i.e., put in the ready queue.
	dispatch_next_thread();
}

//

int uthread_create(void * (*start_routine)(void*), void * arg)
{

}

void uthread_yield()
{
	int has_yielded = 0;

	Save(Running()); // Saves 'here' as current thread context.

	if(!has_yielded) // Stop thread only if thread has not yielded yet.
	{
		has_yielded = 1;
		change_current_thread();
	}
	else // If thread has yielded, we're returning to this point via context switching: we don't stop the thread, just return.
	{
		return;
	}
}

int uthread_join(TCB* waited_for)
{
	TCB* this_thread = Running();
	
	Block(this_thread, waited_for); // Blocks this thread's TCB

	Save(this_thread); // Saves 'here' as current thread context.

	if(Is_Blocked(this_thread)) // Stop thread only if thread is blocked.
	{
		change_current_thread();
	}
	else // If thread isn't blocked, we're returning to this point via context switching: we don't stop the thread, just return.
	{
		return 1;
	}
}

