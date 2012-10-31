#pragma once

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TCB.h"

#define NO_ERROR 0
#define OUT_OF_MEMORY_ERROR NULL
#define LIST_CREATION_ERROR NULL
#define LIST_ADD_ERROR -1
#define LIST_REMOVE_ERROR NULL
#define LIST_CONTAINS_ERROR -1
#define LIST_GET_ERROR NULL
#define TCB_LIST_TO_STRING_ERROR NULL
#define PRINT_TCB_LIST_ERROR -1


typedef struct TCB_struct TCB;

struct TCB_list_node_struct
{
	struct TCB_struct* data;
	struct TCB_list_node_struct* previous;
	struct TCB_list_node_struct* next;
};

struct TCB_list_struct
{
	struct TCB_list_node_struct* front;
	struct TCB_list_node_struct* rear;
};

typedef struct TCB_list_node_struct TCB_list_node;

typedef struct TCB_list_struct TCB_list;

TCB_list* TCB_list_create();
int TCB_list_is_empty(TCB_list* tcb_list);
int TCB_list_add(TCB_list* tcb_list, TCB* tcb);
TCB* TCB_list_remove(TCB_list* tcb_list, TCB* tcb);
int TCB_list_contains(TCB_list* tcb_list, TCB* tcb);
TCB* TCB_list_get(TCB_list* tcb_list, int tid);
char* TCB_list_enumerate_tids(TCB_list* tcb_list);
char* TCB_list_to_string(TCB_list* tcb_list);
int Print_TCB_list(TCB_list* tcb_list);
TCB_list* TCB_list_clone(TCB_list* tcb_list);
