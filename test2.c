#include <stdio.h>
#include <stdlib.h>
#include "../include/uthread.h"

void* f1(int* x)
{
	int i = *x;
	uthread_yield();
	printf("f1: %d\n", i);
	uthread_exit();

	return NULL;
}

void* f2(int* x)
{
	int i = *x;
	uthread_yield();
	printf("f2: %d\n", i);

	return NULL;
}

int main()
{
	int i1 = 1, i2 = 2;
	int id1,id2;
  	
	uthread_init();

  	id1 = uthread_create((void* (*)(void*))f1, &i1);
  	id2 = uthread_create((void* (*)(void*))f2, &i2);
  	uthread_join(id1);
  	uthread_join(id2);

	return 0;
}
