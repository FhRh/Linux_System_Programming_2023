#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
char* args[] = {"vi", "test.txt", NULL};
	int ret;
	//ret = execl("/usr/bin/vi", "vi", "test.txt", NULL);
	//ret = execlp("vi", "vi", "test.txt", NULL);
	//ret = execv("/usr/bin/vi", args);
	ret = execvp("vi", args);
	
	if(ret == -1)
		perror("execl");
	
	return 0;
}