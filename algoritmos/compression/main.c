#include "compression.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Usage: %s <filename>\n", argv[0]);
	}	
	FILE* f = fopen(argv[1], "r");
	if(f == NULL){
		printf("File does not exist.\n");
		return 1;
	}
	fseek(f, 0L, SEEK_END);
	int lines_len = ftell(f);
	if(lines_len <= 0){
		printf("File is empty.\n");
		return 1;
	}
	unsigned char* lines = malloc(sizeof(*lines) * lines_len);
	memset(lines, 0, lines_len);
	rewind(f);
	int i = 0;
	int c;
	while((c = fgetc(f)) != EOF){
		*(lines+i) = c;
		i++;
	}

	huffman_coding(lines, lines_len);
	fclose(f);
	free(lines);
	return 0;
}
