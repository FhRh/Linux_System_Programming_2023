#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_WORDS_COUNT 10000
#define MAX_WORD_LENGTH 1000

sem_t *mySemaphore;

int compareIgnoreCase(const void *a, const void *b) {
    return strcasecmp(*(const char **)a, *(const char **)b);
}

int saveWords(const char *filename, char **result, int word_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        exit(0);
    }
	
	char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) 
      result[word_count++] = strdup(word);                  
    
    fclose(file);
	
	return word_count;
}

void writeWord(const char* filename, const char* newWord) {
	//잠금
    sem_wait(mySemaphore);
	
	//쓸 파일을 연다
	FILE *outputFile = fopen(filename, "r+");
	if (outputFile == NULL) {
        perror("Error opening output file");
        return ;
    }
	
	//단어를 전부 읽어 오고 새로운 단어를 추가한다.
	char** words = (char**)malloc(MAX_WORDS_COUNT);
	char word[MAX_WORD_LENGTH];
	int wordCount = 0;
	while (fscanf(outputFile, "%s", word) == 1) {
        words[wordCount++] = strdup(word);
    }
	words[wordCount++] = strdup(newWord);
	
	qsort(words, wordCount, sizeof(char *), compareIgnoreCase); //정렬
	
	//처음부터 다 옮겨 적는다
	fseek(outputFile, 0, SEEK_SET);
    for (int i = 0; i < wordCount; i++) {
        fprintf(outputFile, "%s ", words[i]);
        free(words[i]); 
    }

	//파일 닫기
    fclose(outputFile);
	
	//잠금 해제
    sem_post(mySemaphore);
	
	return ;
}


void truncateOutputFile(const char* filename){
	int file_descriptor = open(filename, O_CREAT | O_RDWR | O_TRUNC);
    if (file_descriptor == -1) {
        perror("Error opening the file");
        return ;
    }

    // 파일 크기를 0으로 설정하여 내용 지우기
    if (ftruncate(file_descriptor, 0) == -1) {
        perror("Error truncating the file");
        close(file_descriptor);
        return ;
    }

    // 파일 닫기
    close(file_descriptor);
}

int main(int argc, char *argv[]) {
	
	truncateOutputFile(argv[argc-1]);
	
	mySemaphore = sem_open("/mySemaphore", O_CREAT | O_EXCL, 0644, 1);
    if (mySemaphore == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
	
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} 
	
	//부모, 자식 프로세스에 할당할 파일의 범위를 지정 
	int pos;
	int end;
	if(pid!=0){ //부모 프로세스면
		pos = 1;
		end = 1+(argc-2)/2;
	} 
	else{
		pos = 1+(argc-2)/2;	
		end = argc-1;
	}
	
	//입력파일 순회하면서
	for(; pos<end; pos++){
		char **words = (char**)malloc(MAX_WORDS_COUNT);
		int word_count = 0;

		//입력 파일의 단어 읽음
		word_count = saveWords(argv[pos], words, word_count); 
		
		//입력 파일의 단어를 하나씩 함수를 사용해 정렬저장
		int word_index=0;
		while(word_index<word_count){
			writeWord(argv[argc-1], words[word_index++]); 		
			if(pid!=0)
				printf("write by parent process\n");
			else
				printf("write by child process\n");
		}
		free(words);
	}
	
	if(pid!=0){
		wait(NULL);
		printf("kill parent process\n");
	}
	else{
		printf("kill child process\n");
	}
	
	sem_unlink("/mySemaphore");
	sem_close(mySemaphore);

    return 0;
}