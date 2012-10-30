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
	printf("\nAdding thread %d to list...\n", t3->tid); TCB_list_add(l,t3); Print_TCB_list(l); printf("\n");
	printf("\nRemoving thread %d and saving content into TCB variable 't4'...\n", t3->tid); t4 = TCB_list_remove(l,t3); Print_TCB_list(l); printf("\n");
	printf("\nRemoving thread %d and saving content into TCB variable 't4'...\n", t1->tid); t4 = TCB_list_remove(l,t1); Print_TCB_list(l); printf("\n");
	printf("\nRemoving thread %d and saving content into TCB variable 't4'...\n", t2->tid); t4 = TCB_list_remove(l,t2); Print_TCB_list(l); printf("\n");
	printf("\nAdding thread %d to list...\n", t3->tid); TCB_list_add(l,t3); Print_TCB_list(l); printf("\n");
	printf("\nRemoving thread %d and saving content into TCB variable 't4'...\n", t3->tid); t4 = TCB_list_remove(l,t3); Print_TCB_list(l); printf("\n");

	printf("\nHugging Joel Carbonera...\n");
}

