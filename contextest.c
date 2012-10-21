#include "scheduler.h"
#include "dispatcher.h"
#include "contexts.h"

void change_current_thread()
{
	Ready(Running());
	TCB* thread = Schedule();
	Dispatch(thread);
}

void yield()
{
	int yeld = 0;

	Save(Running());

	if(!yeld)
	{
		yeld = 1;
		change_current_thread();
	}
}

void proc1(void* n)
{
	int i = ((int*)n)[0];

	printf("Hello from proc1\n");

	for(; i > 0; i--)
	{
		printf("i=%d\n", i);

		if(i % 3 == 0)
		{
			yield();
		}
	}
}

void proc2(void* n)
{
	int i = ((int*)n)[0];

	printf("Hello from proc2\n");

	for(; i > 0; i--)
	{
		printf("j=%d\n", i);
		yield();
	}
}

int main()
{
	ucontext_t* uclink;
	ucontext_t* context1;
	ucontext_t* context2;
	ucontext_t maincontext;
	int gotcontext = 0;
	int n[1];

	n[0] = 20;

	Init_scheduler();

	uclink = Make_context_noargs(change_current_thread, NULL);

	context1 = Make_context(proc1, (void*)n, uclink);
	context2 = Make_context(proc2, (void*)n, uclink);

	Create(context1);
	Create(context2);

	setcontext(uclink);
}
