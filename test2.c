#include "uthread.h"

// Status atual: NONE

void* f1(int* x)
{
	int i = *x;
	uthread_yield();
	printf("f1: %d", i);
	uthread_exit();
}

void* f2(int* x)
{
	int i = *x;
	uthread_yield();
	printf("f2: %d", i);
	uthread_exit(); 
}

int main()
{
	int i1 = 1, i2 = 2;
	int id1,id2;
  	
	uthread_init();

  	id1 = uthread_create(f1, &i1);
  	id2 = uthread_create(f2, &i2);
  	uthread_join(id1);
  	uthread_join(id2);
}
