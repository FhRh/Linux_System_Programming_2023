#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define MAX_SLEEP 5
#define MAX_SIZE 32
#define INIT_BALANCE 1000
#define MAX_AMOUNT_TO_WITHDRAW 100


struct account{
	pthread_mutex_t* mutex;
	int balance;
};

struct thread_info{
	struct account* saving;
	char name[MAX_SIZE];
};

void* start_routine(void*);
int withdraw(struct account*, char*, int);

int main(void){
	pthread_t t1, t2;
	pthread_mutex_t mutex;
	
	pthread_mutex_init(&mutex, NULL);
	
	struct account saving;
	saving.balance = INIT_BALANCE;
	saving.mutex = &mutex;
	
	struct thread_info owner1;
	struct thread_info owner2;
	
	owner1.saving = &saving;
	strcpy(owner1.name, "Due");
	owner2.saving = &saving;
	strcpy(owner2.name, "Lee");
	
	pthread_create(&t1, NULL, start_routine, (void*) &owner1);
	pthread_create(&t2, NULL, start_routine, (void*) &owner2);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	return 0;
}

void* start_routine(void* owner){
	srand(time(NULL));
	
	for(int i=0; i<5; i++){
		sleep(rand()%MAX_SLEEP);
		int amount_to_withdraw = rand()%MAX_AMOUNT_TO_WITHDRAW+1;
		
		struct thread_info* nowOwner = (struct thread_info*)owner;
		withdraw(nowOwner->saving, nowOwner->name, amount_to_withdraw);
	}
	
	return ((struct thread_info*)owner)->name;
}

int withdraw(struct account* account, char* name, int amount){
	pthread_mutex_lock(account->mutex);
	const int balance = account->balance;
	
	if(balance < amount){
		pthread_mutex_unlock(account->mutex);
		return -1;
	}
	
	account->balance = balance-amount;
	printf("%s withdraw %d. \n", name, amount);
	printf("Current balance : %d. \n", account->balance);
	pthread_mutex_unlock(account->mutex);
	
	return 0;
}
