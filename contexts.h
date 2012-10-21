#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

ucontext_t* Make_context_noargs(void (*start_routine) (void), ucontext_t* uclink);
ucontext_t* Make_context(void (*start_routine) (void*), void* arg, ucontext_t* uclink);
