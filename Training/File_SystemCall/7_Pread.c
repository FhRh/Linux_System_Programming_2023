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
	
	
	ssize_t ret;
	char buf[1024];
	ret = pread(fd, buf, 10, SEEK_SET);		//10까지 읽는거
	if(ret==-1){
		perror("pread");
		return 1;
	}
	buf[ret]='\0';
	printf("%s\n", buf);
	
	close(fd);
	
	return 0;
}