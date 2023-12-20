#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	int status;
	
	pid_t childPid;
	childPid = fork();
	
	if(childPid>0){
		int ret;
		printf("부모시작\n부모 pid : %ld, 자식 pid : %d\n", (long)getpid(), childPid);
		sleep(3);
		
		ret = waitpid(childPid, &status, 0);
		
		printf("부모 프로세스 종료 %d %d %d\n", ret, WIFEXITED(status), WEXITSTATUS(status));
		exit(0);
	}
	else if(childPid==0){
		printf("자식 시작\n자식 pid : %ld\n", (long)getpid());
		sleep(8);
		
		printf("자식 종료\n");
		exit(0);
	}
	else{
		perror("fork");
		return -1;
	}
	
	return 0;
}