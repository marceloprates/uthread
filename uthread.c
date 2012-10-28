#include "uthread.h"

ucontext_t* on_thread_exit;

int Dispatch_next_thread()
{
	TCB* thread = Schedule();

	if(thread != NULL)
	{
		Dispatch(thread);

		return -1; // If execution reached this point, an error ocurred
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

int Is_error(int code)
{
	return code < 0;
}

//

int uthread_init()
{
	ucontext_t* main_context = (ucontext_t*)malloc(sizeof(ucontext_t));
	int error;
	int code;
	int gotcontext = 0;

	if(main_context == NULL) return OUT_OF_MEMORY_ERROR;

	code = Init_scheduler();

	if(Is_error(code)) return OUT_OF_MEMORY_ERROR;

	on_thread_exit = Make_context_noargs(Exit_thread, NULL); // Context to be entered when the thread exits

	if(on_thread_exit == NULL) return MAKE_CONTEXT_ERROR;

	error = getcontext(main_context);

	if(!gotcontext)
	{
		gotcontext = 1;

		if(error) return GET_CONTEXT_ERROR;

		// Sets the context to run when the main thread exits, so that other threads can keep running
		main_context->uc_link = on_thread_exit;

		code = Create(main_context); // Creates main thread

		if(Is_error(code)) return CREATE_THREAD_ERROR;

		// Sets main thread to run; this is necessary so the running context is the one with its uc_link set to on_thread_exit
		code = Dispatch_next_thread();

		if(Is_error(code)) return SCHEDULING_ERROR;
	}

	return NO_ERROR; // If this point was reached, no error ocurred
}

int uthread_create(void * (*start_routine)(void*), void * arg)
{
	ucontext_t* thread_context;
	int code;

	thread_context = Make_context(start_routine, arg, on_thread_exit); // Create thread context that runs start_routine

	if(thread_context == NULL) return MAKE_CONTEXT_ERROR;

	code = Create(thread_context); // Creates thread and inserts it on queue

	if(Is_error(code)) return CREATE_THREAD_ERROR;

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
		return -1;
	
	TCB_block(waited_thread, this_thread); // Blocks this thread's TCB

	Save(this_thread); // Saves 'here' as current thread context.

	if(TCB_is_blocked(this_thread)) // Stop thread only if thread is blocked.
	{
		Dispatch_next_thread();
	}
	else // If thread isn't blocked, we're returning to this point via context switching: we don't stop the thread, just return.
	{
		return 0;
	}
}

void uthread_exit()
{
	// Does nothing
}
