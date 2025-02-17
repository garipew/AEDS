#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int shift_and(char*, char*, size_t, size_t);


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
	printf("%s aparece %d vezes em %s\n", needle, shift_and(needle, lines, needle_len, lines_len), argv[1]);
	fclose(f);
	free(lines);

	return 0;
}


unsigned int* criar_mascara(char* needle, size_t needle_len){
	unsigned int *masks = malloc(sizeof(*masks)*needle_len);
	if(masks == NULL){
		printf("uh oh\n");
		return masks;
	}
	memset(masks, 0, sizeof(*masks)*needle_len);
	char* c;
	for(int i = 0; i < needle_len; i++){
		c = strchr(needle, *(needle+i));
		*(masks+(c-needle)) += 1u<<i;
	}
	return masks;
}


int shift_and(char* needle, char* haystack, size_t needle_len, size_t haystack_len){
	int ocurrences = 0;
	unsigned int r = 0;
	unsigned int* masks = criar_mascara(needle, needle_len);
	if(masks == NULL){
		printf("uh oh\n");
		return ocurrences;
	}
	char* src = NULL;
	int index = -1;
	for(int i = 0; i < haystack_len; i++){
		if((src = strchr(needle, *(haystack+i)))){
			index = src - needle;
		}
		r = ((r<<1) | 1u) & (index < 0 ? 0u : *(masks + index));
		index = -1;
		if(r & 1u<<needle_len-1){
			ocurrences++;
		}
	}
	free(masks);
	return ocurrences;
}
