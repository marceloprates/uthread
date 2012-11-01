#include <stdlib.h>
#include <stdio.h>
#include "../include/uthread.h"

struct range_s
{
	int min;
	int max;
};

typedef struct range_s range_t;

int sum = 0;

void* sum_range(void* range)
{
	range_t* r = (range_t*) range;

	if(r->min == r->max)
	{
		sum += r->min;
	}
	else
	{
		int middle = (r->max + r->min) / 2; // Integer division, is rounded down
		range_t range1;
		range_t range2;

		range1.min = r->min;
		range1.max = middle;
		range2.min = middle + 1;
		range2.max = r->max;

		int tid1 = uthread_create(sum_range, &range1);
		int tid2 = uthread_create(sum_range, &range2);

		if(tid1 == -1 || tid2 == -1)
		{
			printf("Error spawning child thread.\n");
		}
		
		uthread_join(tid1);
		uthread_join(tid2);
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Unsufficient arguments. Please provide two positive integers.\n");
		return 0;
	}

	int n1 = atoi(argv[1]);
	int n2 = atoi(argv[2]);

	if(n1 < 0 || n2 < 0)
	{
		printf("Negative argument. Please provide two positive integers.\n");
		return 0;
	}

	if(n1 > n2)
	{
		printf("%d is larger than %d. First argument can't be larger than the second.\n", n1, n2);
		return 0;
	}

	range_t range;
	range.min = n1;
	range.max = n2;

	int init_status = uthread_init();

	if(init_status != 0)
	{
		printf("Error initializing thread library. Aborting execution.\n");
		return -1;
	}

	int tid = uthread_create(sum_range, &range);

	if(tid == -1)
	{
		printf("Error creating thread. Aborting execution.\n");
		return -1;
	}

	int join_status = uthread_join(tid);

	if(join_status != 0)
	{
		printf("Error joining thread. Aborting execution.\n");
		return -1;
	}

	printf("The final sum was %d.\n", sum);

	return 0;
}
