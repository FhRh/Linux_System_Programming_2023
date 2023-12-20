#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (void){
	printf("uid : %u\n", getuid());
	printf("effective uid : %u\n", geteuid());
	printf("gid : %u\n", getgid());
	
	setuid(14);
	
	printf("uid : %u\n", getuid());
	printf("effective uid : %u\n", geteuid());
	printf("gid : %u\n", getgid());
	
	if(seteuid(0)==-1)	// 오류 발생 effective uid가 루트가 아니라 그런듯
		perror("setuid");
	
	printf("uid : %u\n", getuid());
	printf("effective uid : %u\n", geteuid());
	printf("gid : %u\n", getgid());
	
	
	return 0;
}