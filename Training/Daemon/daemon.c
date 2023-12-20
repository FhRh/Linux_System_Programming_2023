#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/limits.h>

int main(int argc, char* argv[]) {
	pid_t pid;
	int i;
	
	pid=fork();
	if(pid==-1)
		return -1;
	else if(pid!=0)
		exit(EXIT_SUCCESS);
	
	if(setsid()==-1)
		return -1;
	
	if(chdir("/workspace/Linux_Programming/src/practice")==-1)
		return -1;
	
	for(i=0; i<NR_OPEN; i++)
		close(i);
	
	open("/dev/null", O_RDWR);	//stdin
	dup(0);	//stdout
	dup(0);	//stderror
		
	FILE* fp = fopen("daemon.txt", "w");
	for(int i=0; i<100; i++){
		fputs("daemon\n", fp);
	}	
	fclose(fp);
	
	return 0;
}