#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>

int main(void){
	int fd;
	
	fd = creat("/workspace/Linux_Programming/src/test.txt", 0664); 
			// 0664
	
	if(fd==-1){
		perror("creat");
		return 0;
	}	
	
	return 0;
}