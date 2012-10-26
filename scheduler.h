#include "TCB_queue.h"

void Init_scheduler(ucontext_t* main_context);

int Create(ucontext_t* starting_context);

int Ready(TCB* thread);

TCB* Schedule();

TCB* Running();
