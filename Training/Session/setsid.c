#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
	pid_t pid;
	
	pid=fork();
	if(pid==-1){
		perror("fork");
		return -1;
	} else if(pid!=0)
		exit(EXIT_SUCCESS);
	
	printf("original sid : %d\n", getsid(0));
	
	
	if(setsid()==-1){
		perror("setsid");
		return -1;
	}
	
	printf("pid : %d\n", getpid());
	printf("new sid : %d\n", getsid(0));
	
	return 0;
}
