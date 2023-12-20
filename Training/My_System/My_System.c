#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int my_system(const char*cmd){
	int status;
	pid_t pid;
	
	pid=fork();
	if(pid==-1)
		return -1;
	
	else if(pid==0){
		
		execl("/bin/sh", "sh", "-c", cmd, NULL);
		
		exit(-1);
	}
	
	if(waitpid(pid, &status, 0)==-1)
		return -1;
	else if(WIFEXITED(status))
		return WEXITSTATUS(status);
	
	return -1;
}

int main(void){
	int ret=0;
	
	do{
		ret = my_system("ls -l");
		if(WIFSIGNALED(ret)&& WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT || WTERMSIG(ret)==0)
			break;
	}while(1);
	
	printf("ret == %d\n", WTERMSIG(ret));
	
	return 0;
}

