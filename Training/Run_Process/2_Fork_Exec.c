#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	char* args[] = {"vi", "test.txt", NULL};
	
	pid_t pid;
	pid=fork();
	
	if(pid>0){
		printf("I'm child process\n");
		
		int ret;
		ret = execvp("vi", args);
		if(ret == -1)
			perror("execl");
	}
	else if(!pid){
		printf("I'm parents process\n");
	}
	else if(pid<0){
		perror("fork");
		return 1;
	}
	
	
	return 0;
}