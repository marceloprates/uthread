#include "TCB.h"
#define STACKSIZE 10485760

ucontext_t* Make_context(void (*start_routine) (void*), void* arg, ucontext_t* uclink)
{
	ucontext_t* context;
	
	getcontext(context);
	context.uc_stack.ss_sp = mmap(NULL,STACKSIZE,PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_GROWSDOWN|MAP_ANONYMOUS,-1,0);
	context.uc_stack.ss_size = STACKSIZE;
	context.uc_link = uclink;
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