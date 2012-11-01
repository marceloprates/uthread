#include <stdlib.h>
#include "scheduler.h"
#include "dispatcher.h"
#include "contexts.h"
#include "uthread.h"

ucontext_t* on_thread_exit; // Context to be entered when the thread exits
int main_tid; // tid belonging to the main thread

static int Dispatch_next_thread()
{
	TCB* thread = Schedule();

	if(thread != NULL)
	{
		Dispatch(thread);

		return ERROR; // If execution reached this point, an error ocurred
	}
	else
	{
		return NO_ERROR; // Ready queue emptied. All threads are now finished.
	}
}

static void Change_current_thread()
{
	Ready(Running()); // Running thread is 'stopped', i.e., put in the ready queue.
	Dispatch_next_thread();
}

static void Exit_thread()
{
	TCB* thread = Running();
	Kill(thread);
	Dispatch_next_thread();
}

static int Is_error(int code)
{
	return code < 0;
}

static int Is_main()
{
	TCB* current_thread = Running();
	return current_thread->tid == main_tid;
}

//

int uthread_init()
{
	ucontext_t* main_context = (ucontext_t*)malloc(sizeof(ucontext_t));
	int result;
	int code;
	int gotcontext = 0;

	if(main_context == NULL) return ERROR;

	code = Init_scheduler();

	if(Is_error(code)) return ERROR;

	on_thread_exit = Make_context_noargs(Exit_thread, NULL); // Context to be entered when a thread exits

	if(on_thread_exit == NULL) return ERROR;

	result = getcontext(main_context);

	if(!gotcontext)
	{
		gotcontext = 1;

		if(result == -1) return ERROR;

		main_tid = Create(main_context); // Creates main thread

		if(Is_error(main_tid)) return ERROR;

		// Sets main thread to run; this is necessary for consistency
		code = Dispatch_next_thread();

		if(Is_error(code)) return ERROR;
	}

	return NO_ERROR; // If this point was reached, no error ocurred
}

int uthread_create(void * (*start_routine)(void*), void * arg)
{
	ucontext_t* thread_context;
	int code;

	thread_context = Make_context(start_routine, arg, on_thread_exit); // Creates thread context that runs start_routine

	if(thread_context == NULL) return ERROR;

	code = Create(thread_context); // Creates thread and inserts it on queue

	if(Is_error(code)) return ERROR;

	return code; // Contains thread id
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

int uthread_join(int waited_thread_tid)
{
	TCB* this_thread = Running();

	TCB* waited_thread = Find_TCB(waited_thread_tid);

	if(waited_thread == NULL) // Thread with 'waited_thread_tid' tid not found. Return -1.
	{
		return ERROR;
	}
	
	Block(this_thread, waited_thread); // Blocks this thread's TCB

	Save(this_thread); // Saves 'here' as current thread context.

	if(TCB_is_blocked(this_thread)) // Stop thread only if thread is blocked.
	{
		return Dispatch_next_thread();
	}
	else // If thread isn't blocked, we're returning to this point via context switching: we don't stop the thread, just return.
	{
		return NO_ERROR;
	}
}

void uthread_exit()
{
	// Does nothing
}

void uthread_wait()
{
	if(Is_main()) // Current thread is the main thread
	{
		while(!No_threads_beside_main()) // Stops execution of main until all other threads have finished
		{
			uthread_yield();
		}
	}
}
