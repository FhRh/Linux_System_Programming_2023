#include <stdio.h>
#include <stdlib.h>

void out(void){
	printf("out succeded\n");
}

void out2(void){
	printf("out2 succeded\n");
}

int main(){
	
	if(atexit(out))
		fprintf(stderr, "out failed\n");
	
	if(atexit(out2))
		fprintf(stderr, "out2 failed\n");
	
	return 0;
}