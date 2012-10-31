#include "TCB_queue.h"

#define MAX_THREADS 128

#define NO_ERROR 0
#define MAX_THREADS_ERROR -1
#define INIT_SCHEDULER_ERROR -1

int	Init_scheduler();
int	Create(ucontext_t* starting_context);
int	Ready(TCB* thread);
TCB*	Schedule();
TCB*	Running();
void	Block(TCB* thread, TCB* waited_for);
void	Unblock(TCB* thread, TCB* waited_for);
void	Unblock_waiting_for_me(TCB* thread);
void	Kill(TCB* thread);
TCB*	Find_TCB(int tid);
int	No_threads_beside_main();
