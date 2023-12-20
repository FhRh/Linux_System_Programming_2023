#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

int main(void){
	struct timespec tp;
	int ret;
	
	ret = sched_rr_get_interval(0, &tp);
	if(ret==-1)
		perror("sched_rr_get_interval");
	
	printf("tv_sec : %ld \n",tp.tv_sec);
	printf("tv_nsec : %fsec\n",tp.tv_nsec/1000000000.0f);
	
	return 0;
}