#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
	
	int fd;
	fd = open("/workspace/Linux_Programming/src/test.txt", O_RDONLY);
	
	if(fd==-1){
		perror("open");
		return 1;
	}	
	
	off_t ret;
	ret = lseek(fd,0,SEEK_END);
	if(ret==-1){
		perror("lseek");
		return 1;
	}
	printf("%ld\n", ret);
	
	close(fd);
	
	return 0;
}