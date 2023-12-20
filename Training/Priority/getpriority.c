#include <stdio.h>
#include <errno.h>
#include <sys/resource.h>

int main(void){
	int ret;
	ret = setpriority(PRIO_PROCESS, 0, 10);
	
	errno=0;
	if(ret==-1 && errno!=0)
		perror("getpriority");
	
	printf("priority : %d\n", getpriority(PRIO_PROCESS, 0));
	
	
	return 0;
}