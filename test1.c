#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

void* proc3(void* n);

void* proc1(void* n)
{
	int i = *(int*)n;

	printf("--Hello from proc1--\n");

	for(; i > 0; i--)
	{
		printf("i=%d\n", i);

		if(i % 3 == 0)
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

	int m;

	m = 42;

	int id3 = uthread_create(proc3, &m);

	if(id3 != -1)
	{
		printf("--Created thread 3--\n");
	}
	else
	{
		printf("--Creation of thread 3 failed--\n");
	}

	for(; i > 0; i--)
	{
		printf("j=%d\n", i);
		uthread_yield();
	}

	return NULL;
}

void* proc3(void* n)
{
	int i = *(int*)n;

	printf("--Hello from proc3--\n");

	for(; i > 0; i--)
	{
		printf("k=%d\n", i);
		uthread_yield();
	}

	return NULL;
}

int main()
{
	int n;
	int id1;
	int id2;

	n = 21;

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

	uthread_wait();

	return 0;
}
