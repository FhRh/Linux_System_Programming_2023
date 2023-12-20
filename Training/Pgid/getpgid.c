#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	pid_t pgid;
	pgid = getpgid(0);
	
	if(pgid==-1)
		perror("getpgid");
	
	printf("pid : %d\n", getpid());
	printf("My process group id=%d\n", getpgid(0));
	
	return 0;
}