#include "scheduler.h"
#include "dispatcher.h"
#include "contexts.h"

ucontext_t* on_exit;

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
	Dispatch_next_thread();
}

void Exit_thread()
{
	TCB* thread = Running();
	free(thread); // Frees pointer to thread that exited
	Dispatch_next_thread();
}

//

int uthread_init()
{
	ucontext_t* main_context = (ucontext_t*)malloc(sizeof(ucontext_t));
	bool gotcontext = 0;

	on_exit = Make_context_noargs(Exit_thread, NULL); // Context to be entered when the thread exits

	getcontext(main_context);

	if(!gotcontext)
	{
		gotcontext = 1;

		// Sets the context to run when the main thread exits, so that other threads can keep running
		main_context->uc_link = on_exit;

		Create(main_context); // Creates main thread

		// Sets main thread to run; this is necessary so the running context is the one with its uc_link set to on_exit
		Dispatch_next_thread(); 
	}

	returns something; // TODO: test for errors
}

int uthread_create(void * (*start_routine)(void*), void * arg)
{
	ucontext_t* thread_context;

	thread_context = Make_context(start_routine, arg, on_exit); // Create thread context that runs start_routine

	Create(thread_context); // Creates thread and inserts it on queue

	returns something; // TODO: test for errors
}

void uthread_yield()
{
	int has_yielded = 0;

	Save(Running()); // Saves 'here' as current thread context.

	if(!has_yielded) // Stop thread only if thread has not yielded yet.
	{
		has_yielded = 1;
		Change_current_thread();
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
		Change_current_thread();
	}
	else // If thread isn't blocked, we're returning to this point via context switching: we don't stop the thread, just return.
	{
		return 1;
	}
}

