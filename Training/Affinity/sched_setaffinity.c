#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

int main(int argc, char* argv[]) {
	cpu_set_t set;
	int ret, i;
	
	CPU_ZERO(&set);
	CPU_SET(1, &set);
	CPU_CLR(0, &set);
	ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);
	if(ret==-1)
		perror("sched_setaffinity");
	for(i=0; i< 100; i++){
		int cpu;
		
		cpu = CPU_ISSET(i, &set);
		printf("cpu=%i is %s\n", i, cpu ? "set" : "unset");
	}
	
	return 0;
}