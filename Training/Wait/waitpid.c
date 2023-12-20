#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	int status;	
	pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
	
	if (pid == 0) {
        exit(EXIT_SUCCESS); 
    }
	
	pid_t exited_child = waitpid(pid, &status, WNOHANG);
	
	if(exited_child==-1)
		perror("waitpid");
	else{
		printf("child_pid=%d exited_pid=%d\n", pid, exited_child);
		
		if(WIFEXITED(status))
			printf("Normal termination with exit status=%d\n", WEXITSTATUS(status));
		
		if(WIFSIGNALED(status))
			printf("Killed by signal=%d%s\n", WTERMSIG(status), WCOREDUMP(status)?"(dumped core)":"");
	}
	
	
	return 0;
}