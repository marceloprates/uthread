#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

void* child(void* n);

void* parent(void* n)
{	
	int i = *(int*)n;

	printf("--Entered parent thread--\n");

	int m = 2 * i;

	int child_id = uthread_create(proc3, &m);

	if(id3 != -1)
	{
		printf("--Created child thread--\n");
	}
	else
	{
		printf("--Creation of child thread failed--\n");
	}

	for(; i > 0; i--)
	{
		printf("Parent: %d\n", i);
		uthread_yield();
	}

	return NULL;
}

void* child(void* n)
{
	int i = *(int*)n;

	printf("--Entered child thread--\n");

	for(; i > 0; i--)
	{
		printf("Child: %d\n", i);
		uthread_yield();
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

	int id;

	uthread_init();
	id = uthread_create(parent, &n);

	if(id != -1)
	{
		printf("--Created parent thread--\n");
	}
	else
	{
		printf("--Creation of parent thread failed--\n");
	}

	uthread_join(id);

	printf("--End of parent thread--\n");

	uthread_wait();

	return 0;
}