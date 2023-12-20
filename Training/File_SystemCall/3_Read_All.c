#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
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
	char *position = buf;
	
	int len=1024;
	while(len!=0 && (ret = read(fd, position, len))!=0 ){
	
		if(ret==-1){
			if(errno==EINTR){
				printf("process stoped\n");
				continue;
			}
			perror("read");
			break;
		}
		
		len -= ret;
		position += ret;
	}
	
	*position = '\0';
	printf("%s\n", buf);
	
	close(fd);
	
	return 0;
}