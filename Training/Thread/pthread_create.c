#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

void* start_routine(void* arg){
	printf("new thread!\n");
	return NULL;
}

int main(void){
	pthread_t thread;
	int ret;
	
	ret = pthread_create(&thread, NULL, start_routine, NULL);
	if(!ret){
		errno = ret;
		perror("pthread_create");
		return -1;
	}
	else{
		printf("ret : %d\n", ret);
		printf("EAGAIN : %d\n", EAGAIN);
		printf("EINAVL : %d\n", EINVAL);
		printf("EPERM : %d\n", EPERM);
	}
	return 0;
}