#include "TCB.h"

ucontext_t* Make_context(void (*start_routine) (void*), void* arg)
{
	ucontext_t* context;
	
	getcontext(context);
	context.uc_stack.ss_sp = ??;
	context.uc_stack.ss_size = ??;
	context.uc_link = ??;
	makecontext(context, start_routine, 1, arg);

	return context;
}

void Dispatch(TCB* thread)
{
	setcontext(thread->context);
}

int Yield(TCB* thread)
{
	int success = getcontext(thread->context);

	return success;
}