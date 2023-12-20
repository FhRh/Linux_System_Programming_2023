#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int policy;
	
	policy = sched_getscheduler(0);
	
	switch(policy) {
		case SCHED_OTHER:
			printf("policy is normal\n");
			break;
		case SCHED_RR:
			printf("policy is round-robin\n");
			break;
		case SCHED_FIFO:
			printf("policy is first-in, first-out\n");
			break;
		case -1:
			perror("sched_getscheduler");
			break;
		default:
			fprintf(stderr, "unknown policy!\n");
	}
	
	
	return 0;
}