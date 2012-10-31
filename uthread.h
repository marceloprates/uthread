#include "scheduler.h"
#include "dispatcher.h"
#include "contexts.h"


#define NO_ERROR 0
#define OUT_OF_MEMORY_ERROR -1
#define MAKE_CONTEXT_ERROR -1
#define GET_CONTEXT_ERROR -1
#define CREATE_THREAD_ERROR -1
#define SCHEDULING_ERROR -1
#define DISPATCH_ERROR -1
#define TCB_NOT_FOUND_ERROR -1;

int uthread_init();

int uthread_create(void * (*start_routine)(void*), void * arg);

void uthread_yield();

int uthread_join(int waited_thread_tid);

void uthread_exit();



