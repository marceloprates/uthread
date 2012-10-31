#include "uthread.h"

// Status atual: PASS

void* f(void* nothing)
{
	static int shared = 0;
	int private = shared;
	shared++;

	printf("I am the thread at index %d!\n", private);

	uthread_yield();

	printf("It's me again, at index %d.\n", private);

	uthread_yield();

	printf("That's enough for today at index %d, goodbye.\n", private);
}

int main()  
{
	int tids[128];
	int i;

	uthread_init();

	for(i = 0; i < 128; i++)
	{
		tids[i] = uthread_create(f, NULL);
	}

	for(i = 0; i < 128; i++)
	{
		uthread_join(tids[i]);
	}
}
