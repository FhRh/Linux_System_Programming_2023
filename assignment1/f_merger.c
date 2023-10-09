#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS_COUNT 10000
#define MAX_WORD_LENGTH 1000

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

int main(int argc, char *argv[]) {
	char **words = (char**)malloc(MAX_WORDS_COUNT);
	int word_count = 0;
	
	for (int i = 1; i < argc-1; i++) {
        word_count = saveWords(argv[i], words, word_count);
    }
	
	qsort(words, word_count, sizeof(char *), compareIgnoreCase);
	
	char* outputFilename = argv[argc-1];
	FILE *output = fopen(outputFilename,"w");
	if (output == NULL) {
        perror("파일을 열 수 없습니다.");
        return 1;
    }
	
	for(int i=0; i<word_count; i++){
		fprintf(output, "%s ", words[i]);
	}
	
    free(words);
	fclose(output);
	
    return 0;
}