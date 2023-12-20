#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(void){
	int fd;
	fd = open("/workspace/Linux_Programming/src/test.txt", O_WRONLY , 0664);
	if(fd==-1){
		perror("open");
		return 1;
	}
	
	int ret;
	
	ret = ftruncate(fd, 10);	//10 뒤로 지움
	if(ret==-1){
		perror("truncate");
		return 1;
	}
	
	return 0;
}