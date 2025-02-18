#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "match.h"


int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Usage: %s <filename> <pattern>\n", argv[0]);
		return 1;
	}
	FILE* f = fopen(argv[1], "r");
	fseek(f, 0L, SEEK_END);
	int lines_len = ftell(f);
	char* lines = malloc(sizeof(*lines) * lines_len);
	memset(lines, 0, lines_len);
	rewind(f);
	char* needle = argv[2];
	int needle_len = strlen(argv[2]);
	int i = 0;
	char c;
	while((c = fgetc(f)) != EOF){
		*(lines+i) = c;
		i++;
	}
	printf("kmp: %d\nshift_and: %d\n", kmp(needle, lines, needle_len, lines_len), shift_and(needle, lines, needle_len, lines_len)); 
	fclose(f);
	free(lines);

	return 0;
}


