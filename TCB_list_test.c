#include <stdlib.h>

#include "TCB.h"
#include "TCB_list.h"

int main(int argc, char *argv[])
{
	TCB_list* l = TCB_list_create();

	TCB* t1 = Create_TCB(1,NULL,ready);
	TCB* t2 = Create_TCB(2,NULL,ready);
	TCB* t3 = Create_TCB(3,NULL,ready);
	TCB* t4 = Create_TCB(4,NULL,ready);
	
	printf("\nAdding thread %d to list...\n",t1->tid); TCB_list_add(l,t1); Print_TCB_list(l); printf("\n");
	printf("\nAdding thread %d to list...\n",t2->tid); TCB_list_add(l,t2); Print_TCB_list(l); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t2->tid); Block(t1,t2); Print_TCB_list(l); printf("\n");
	printf("\nAdding thread %d to list...\n", t3->tid); TCB_list_add(l,t3); Print_TCB_list(l); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t3->tid); Block(t1,t3); Print_TCB_list(l); printf("\n");
	printf("\nRemoving thread %d and saving content into TCB variable 't4'...\n", t1->tid); t4 = TCB_list_remove(l,t1); Print_TCB_list(l); printf("\n");
	printf("\nAdding TCB variable 't4' A.K.A. thread %d to list...\n",t4->tid); TCB_list_add(l,t4); Print_TCB_list(l); printf("\n");
	printf("\nUnblocking thread %d with thread %d...\n",t1->tid,t2->tid); Unblock(t1,t2); Print_TCB_list(l); printf("\n");
	printf("\nUnblocking thread %d with thread %d...\n",t1->tid,t3->tid); Unblock(t1,t3); Print_TCB_list(l); printf("\n");
	printf("\nHugging Joel Carbonera...\n");
}

