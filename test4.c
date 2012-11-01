#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

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

	return NULL;
}

int main(int argc, char* argv[])  
{
	if(argc < 2)
	{
		printf("Provide a number of threads to create.\n");
		return 0;
	}

	int n = atoi(argv[1]);

	if(n < 1)
	{
		printf("The number of threads must be a positive number.\n");
		return 0;
	}

	int* tids = (int*)calloc(n, sizeof(int));
	int i;

	uthread_init();

	for(i = 0; i < n; i++)
	{
		tids[i] = uthread_create(f, NULL);
		
		if(tids[i] == -1)
		{
			printf("Couldn't create thread at index %d...\n", i);
		}
	}

	for(i = 0; i < n; i++)
	{
		uthread_join(tids[i]);
	}

	return 0;
}
