#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

int b;  // Single buffer of size 1

void add_buffer(int i)
{
	b = i;
}

int get_buffer()
{
	return b ;
}

void* producer(void* nothing)
{
	int i = 0;
	printf("I'm a producer\n");

	while (1)
	{
  		add_buffer(i);
  		i = i + 1;
		uthread_yield();
	}
	
	return NULL;
}

void* consumer(void* n)
{
	int i,v;
	int max = *(int*)n;

	printf("I'm a consumer\n");

	for (i=0;i<max;i++)
	{
   		v = get_buffer();
   		printf("got %d  ",v);
		uthread_yield();
	}

	printf("\n");

	return NULL;
}
 
int main(int argc, char* argv[])  
{
	if(argc < 2)
	{
		printf("Not enough arguments, inform a number of iterations.\n");
		return 0;
	}

	int n = argv[1];

        if(n < 0)
        {
		printf("Negative argument. Please enter a positive integer as argument.\n");
		return 0;
	}

	int consumer_tid;

	uthread_init();

	uthread_create(producer, NULL);
	consumer_tid = uthread_create(consumer, &n);

	uthread_join(consumer_tid);

	return 0;
}
 

