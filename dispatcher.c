#include <sys/mman.h>
#include "dispatcher.h"
#define STACKSIZE 10485760

void Dispatch(TCB* thread)
{
	setcontext(thread->context);
}

int Save(TCB* thread)
{
	int success = getcontext(thread->context);

	return success;
}
