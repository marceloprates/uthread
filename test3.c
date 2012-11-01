#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

int b;  /* buffer size = 1; */

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

void* consumer(void* nothing)
{
	int i,v;
	printf("I'm a consumer\n");

	for (i=0;i<100;i++)
	{
   		v = get_buffer();
   		printf("got %d  ",v);
		uthread_yield();
	}

	return NULL;
}
 
int main()  
{
	int consumer_tid;

	uthread_init();

	uthread_create(producer, NULL);
	consumer_tid = uthread_create(consumer, NULL);

	uthread_join(consumer_tid);

	return 0;
}
 

