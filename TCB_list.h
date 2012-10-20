#pragma once

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TCB.h"

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
char* TCB_list_to_string(TCB_list* tcb_list);
int Print_TCB_list(TCB_list* tcb_list);
