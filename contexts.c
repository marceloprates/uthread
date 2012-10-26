#define MAKECONTEXT

#include <sys/mman.h>
#include "contexts.h"
#define STACKSIZE 10485760

ucontext_t* Make_context_noargs(void (*start_routine) (void), ucontext_t* uclink)
{
	ucontext_t* cp = (ucontext_t*)malloc(sizeof(ucontext_t));

	if(cp == NULL)
	{
		printf("\n * Make_context_noargs: Context not created. No memory avaliable * \n");

		return NULL;
	}
	else
	{
		getcontext(cp);
		cp->uc_stack.ss_sp = mmap(NULL,STACKSIZE,PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_GROWSDOWN|MAP_ANONYMOUS,-1,0);
		cp->uc_stack.ss_size = STACKSIZE;
		cp->uc_link = uclink;

		makecontext(cp, start_routine, 0);

		return cp;
	}
}

#ifdef MAKECONTEXT 
ucontext_t* Make_context(void (*start_routine) (void*), void* arg, ucontext_t* uclink)
{
	ucontext_t* cp = (ucontext_t*)malloc(sizeof(ucontext_t));

	if(cp == NULL)
	{
		printf("\n * Make_context: Context not created. No memory avaliable * \n");

		return NULL;
	}
	else
	{
		getcontext(cp);
		cp->uc_stack.ss_sp = mmap(NULL,STACKSIZE,PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_GROWSDOWN|MAP_ANONYMOUS,-1,0);
		cp->uc_stack.ss_size = STACKSIZE;
		cp->uc_link = uclink;

		makecontext(cp, (void (*)(void))start_routine, 1, arg);

		return cp;
	}
}

#else /*ifndef MAKECONTEXT*/

ucontext_t* Make_context(void (*start_routine) (void*), void* arg, ucontext_t* uclink)
{
	ucontext_t* cp = (ucontext_t*)malloc(sizeof(ucontext_t));

	if(cp == NULL)
	{
		printf("\n * Make_context: Context not created. No memory avaliable * \n");

		return NULL;
	}
	else
	{
		bool contextsaved = 0;
		bool contextentered = 0;
	
		getcontext(cp);

		if(!gotcontext)
		{
			gotcontext = 1;
			start_routine(arg);
		}

		return cp;
	}
}

#endif /*MAKECONTEXT*/
