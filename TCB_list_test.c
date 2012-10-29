#include <stdlib.h>

#include "TCB.h"
#include "TCB_list.h"

int main(int argc, char *argv[])
{
	TCB_list* l = TCB_list_create();

	TCB* t1 = TCB_create(1,NULL,ready);
	TCB* t2 = TCB_create(2,NULL,ready);
	TCB* t3 = TCB_create(3,NULL,ready);
	TCB* t4 = TCB_create(4,NULL,ready);
	
	printf("\nAdding thread %d to list...\n",t1->tid); TCB_list_add(l,t1); Print_TCB_list(l); printf("\n");
	printf("\nAdding thread %d to list...\n",t2->tid); TCB_list_add(l,t2); Print_TCB_list(l); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t2->tid); TCB_block(t1,t2); Print_TCB_list(l); printf("\n");
	printf("\nAdding thread %d to list...\n", t3->tid); TCB_list_add(l,t3); Print_TCB_list(l); printf("\n");
	printf("\nBlocking thread %d with thread %d...\n",t1->tid,t3->tid); TCB_block(t1,t3); Print_TCB_list(l); printf("\n");
	printf("\nRemoving thread %d and saving content into TCB variable 't4'...\n", t1->tid); t4 = TCB_list_remove(l,t1); Print_TCB_list(l); printf("\n");
	printf("\nAdding TCB variable 't4' A.K.A. thread %d to list...\n",t4->tid); TCB_list_add(l,t4); Print_TCB_list(l); printf("\n");
	printf("\nUnblocking thread %d with thread %d...\n",t1->tid,t2->tid); TCB_unblock(t1,t2); Print_TCB_list(l); printf("\n");
	printf("\nUnblocking thread %d with thread %d...\n",t1->tid,t3->tid); TCB_unblock(t1,t3); Print_TCB_list(l); printf("\n");
	printf("\nSearching list for thread %d...\n", 3); TCB* aux = (TCB*)malloc(sizeof(TCB)); aux = TCB_list_get(l,3);
	printf("\nThread %d found. Printing thread...\n", 3); printf("\n%s\n", TCB_to_string(aux));
	printf("\nChanging thread %d state to 'running'\n", t3->tid); t3->state = running;
	printf("\nSearching list for thread %d...\n", 3); aux = (TCB*)malloc(sizeof(TCB)); aux = TCB_list_get(l,3);
	printf("\nThread %d found. Printing thread...\n", 3); printf("\n%s\n", TCB_to_string(aux));
	
	printf("\nHugging Joel Carbonera...\n");
}

