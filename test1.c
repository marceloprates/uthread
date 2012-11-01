#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

void* proc1(void* n)
{
	int i = *(int*)n;

	printf("--Hello from proc1--\n");

	for(; i > 0; i--)
	{
		printf("i=%d\n", i);

		if(i % 5 == 0)
		{
			uthread_yield();
		}
	}

	return NULL;
}

void* proc2(void* n)
{	
	int i = *(int*)n;

	printf("--Hello from proc2--\n");

	for(; i > 0; i--)
	{
		printf("j=%d\n", i);

		if(i % 3 == 0)
		{
			uthread_yield();
		}
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
        {
		printf("Please enter a positive integer as argument.\n");
		return 0;
	}

        int n = atoi(argv[1]);

        if(n < 0)
        {
		printf("Negative argument. Please enter a positive integer as argument.\n");
		return 0;
	}

	uthread_init();
	id1 = uthread_create(proc1, &n);

	if(id1 != -1)
	{
		printf("--Created thread 1--\n");
	}
	else
	{
		printf("--Creation of thread 1 failed--\n");
	}

	id2 = uthread_create(proc2, &n);

	if(id2 != -1)
	{
		printf("--Created thread 2--\n");
	}
	else
	{
		printf("--Creation of thread 2 failed--\n");
	}

	uthread_join(id1);
	uthread_join(id2);

	printf("--End of main--\n");

	return 0;
}
