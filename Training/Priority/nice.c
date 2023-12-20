#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(void){
	int ret;
	
	errno = 0;
	ret = nice(15);
	if(ret==-1 && errno!=0)
		perror("nice");
	else
		printf("nice value is now %d\n", ret);
	
	return 0;
}