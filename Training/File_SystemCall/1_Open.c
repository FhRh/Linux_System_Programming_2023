#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(void){
	int fd;
	
	fd = open("/workspace/Linux_Programming/src/test.txt", O_WRONLY | O_CREAT | O_TRUNC,
			 0664); 
			// 0664
	
	if(fd==-1){
		perror("open");
		return 1;
	}	
	
	close(fd);
	
	return 0;
}