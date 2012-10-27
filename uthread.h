#include "scheduler.h"
#include "dispatcher.h"
#include "contexts.h"

int uthread_init();

int uthread_create(void * (*start_routine)(void*), void * arg);

void uthread_yield();

int uthread_join(TCB* waited_for);

void uthread_exit();



