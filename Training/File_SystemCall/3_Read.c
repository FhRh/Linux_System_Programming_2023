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
	
	ssize_t nr;
	char buf[1024];
	
	nr = read(fd, &buf, sizeof(buf));
	
	if(nr==-1){
		perror("read");
		return 1;
	}
	
	buf[nr] = '\0';
	
	printf("%zd\n", nr);
	printf("%s\n", buf);
	
	close(fd);
	
	return 0;
}