#include <stdlib.h>

#include "TCB.h"
#include "TCB_queue.h"

int main(int argc, char *argv[])
{
	TCB_queue* q = TCB_queue_create();

	TCB* t1 = TCB_create(1,NULL,ready);
	TCB* t2 = TCB_create(2,NULL,ready);
	TCB* t3 = TCB_create(3,NULL,ready);
	TCB* t4 = TCB_create(4,NULL,ready);
	
	printf("\nEnqueuing thread %d...\n",t1->tid); Enqueue(q,t1); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing thread %d...\n",t2->tid); Enqueue(q,t2); Print_TCB_queue(q); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t2->tid); TCB_block(t1,t2); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing thread %d...\n", t3->tid); Enqueue(q,t3); Print_TCB_queue(q); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t3->tid); TCB_block(t1,t3); Print_TCB_queue(q); printf("\n");
	printf("\nDenqueuing and saving content into TCB variable 't4'...\n"); t4 = Dequeue(q); Print_TCB_queue(q); printf("\n");
	printf("\nEnqueuing TCB variable 't4' A.K.A. thread %d...\n",t4->tid); Enqueue(q,t4); Print_TCB_queue(q); printf("\n");
	printf("\nUnblocking all threads waiting for thread %d\n",t1->tid); TCB_unblock_waiting_for_me(t1); Print_TCB_queue(q); printf("\n");
	//printf("\nUnblocking thread %d with thread %d...\n",t1->tid,t2->tid); TCB_Unblock(t1,t2); Print_TCB_queue(q); printf("\n");
	//printf("\nUnblocking thread %d with thread %d...\n",t1->tid,t3->tid); TCB_Unblock(t1,t3); Print_TCB_queue(q); printf("\n");
	printf("\nHugging Joel Carbonera...\n");
}
