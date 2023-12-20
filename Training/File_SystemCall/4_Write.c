#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>

int main(void){
	int fd;
	
	fd = open("/workspace/Linux_Programming/src/test.txt", O_WRONLY | O_CREAT | O_TRUNC, 
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); 
			// 0664
	
	if(fd==-1){
		perror("open");
		return 0;
	}
	
	ssize_t ret;
	char *buf = "It is a write call";
	char *position = buf;
	int len=strlen(buf);
	while(len!=0 && (ret=write(fd,position,len))!=0){
		if(ret==-1){
			if(errno=EINTR)
				continue;
			perror("write");
			return 1;
		}
		
		len -= ret;
		position += ret;
	}
	
	close(fd);
	
	return 0;
}