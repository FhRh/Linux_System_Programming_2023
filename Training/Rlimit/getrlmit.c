#include <stdio.h>
#include <sys/resource.h>

int main(void){
	struct rlimit rlim;
	int ret;
	
	ret = getrlimit(RLIMIT_CORE, &rlim);;
	if(ret==-1){
		perror("getrlimit");
		return 1;
	}
	printf("RLIMIT_CORE : soft=%ld hard=%ld\n", rlim.rlim_cur, rlim.rlim_max);
	
	rlim.rlim_cur = 5;
	rlim.rlim_max = 100;
	
	ret = setrlimit(RLIMIT_CORE, &rlim);
	ret = getrlimit(RLIMIT_CORE, &rlim);;
	if(ret==-1){
		perror("getrlimit");
		return 1;
	}
	printf("RLIMIT_CORE : soft=%ld hard=%ld\n", rlim.rlim_cur, rlim.rlim_max);
	
	return 0;
}