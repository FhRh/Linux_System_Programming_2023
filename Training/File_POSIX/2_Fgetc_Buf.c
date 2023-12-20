#include <stdio.h>

int main(void){
	
	FILE* fp;
	
	fp = fopen("/workspace/Linux_Programming/src/test.txt", "r+");
	if(!fp){
		perror("open");
	}
	
	char buf[1024];
	char* pos = buf;
	int c;
	while((c=fgetc(fp))!=EOF){
		*pos++ = (char)c;
	}
	*pos='\0';
	printf("%s\n", buf);
	
	fclose(fp);
	
	return 0;
}