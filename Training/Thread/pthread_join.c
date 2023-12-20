#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_SLEEP 10

void* start_routine(void *message){
	srand(time(NULL));
	
	for(int i=0; i<5; i++){
		sleep(rand()%MAX_SLEEP);
		printf("%s\n", (const char *) message);
	}
	
	return message;
}

int main(void){
	pthread_t t1, t2;
	const char* message1 = "Thread 1";
	const char* message2 = "Thread 2";
	
	pthread_create(&t1, NULL, start_routine, (void*) message1);
	pthread_create(&t2, NULL, start_routine, (void*) message2);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	return 0;
}