
#define NO_ERROR 0
#define ERROR -1

int uthread_init();

int uthread_create(void * (*start_routine)(void*), void * arg);

void uthread_yield();

int uthread_join(int waited_thread_tid);

void uthread_exit();



