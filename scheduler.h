#include "TCB.h"

void Init_scheduler();

int Create(ucontext_t* starting_context);

int Ready(TCB* thread);

TCB* Schedule();

TCB* Running();