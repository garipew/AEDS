#include "hash.h"
#include <stdlib.h>
#include <stdio.h>


char* get_word(FILE* stream){
	int c;
	int count = 0;
	char* word;
	long start = ftell(stream);
	while((c = getc(stream)) != EOF && (c == '\n' || c == '\t')){ start++; }
	ungetc(c, stream);
	while((c = getc(stream)) != EOF && c != ' ' && c != '\n'){
		count++;
	}	
	if(count == 0){
		return NULL;
	}
	fseek(stream, start, SEEK_SET);
	word = malloc(count+1);
	if(!word){
		return word;
	}
	while((c = getc(stream)) != EOF && c != ' ' && c != '\n'){
		*word++ = c;
	}
	if(*(word-1) > 'z' || *(word-1) < 'A' || (*(word-1) > 'Z' && *(word-1) < 'a')){
		*(word-1) = '\0';
	}
	*word = '\0';
	return word-count;
}


int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
	Hash* h = criar_hash();
	if(!h){
		printf("%s: Unexpected fail\n", argv[0]);
		return 1;
	}
	FILE* f = fopen(argv[1], "r");
	if(!f){
		printf("%s: Unable to read %s\n", argv[0], argv[1]);
		return 1;
	}
	char* word;
	while((word = get_word(f)) != NULL){
		if(!install(h, word)){
			free(word);
		}
	}
	write_hash(h);
	cleanup(h);
	fclose(f);
	return 0;
}
