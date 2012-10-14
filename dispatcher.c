#include "TCB.h"

void Dispatch(TCB* thread)
{
	setcontext(thread->context);
}

int Yield(TCB* thread)
{
	ucontext_t* ucp;

	int success = getcontext(ucp);

	if(success == 0)
	{
		thread->context = ucp;
	}

	return success;
}
