#include "dispatcher.h"

void Dispatch(TCB* thread)
{
	setcontext(thread->context);
}

int Save(TCB* thread)
{
	int success = getcontext(thread->context);

	return success;
}
