#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "match.h"


unsigned int* pre_shift_and(char* needle, size_t needle_len){
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
	int count = 0;
	unsigned int r = 0;
	unsigned int* masks = pre_shift_and(needle, needle_len);
	if(masks == NULL){
		printf("uh oh\n");
		return count;
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
			count++;
		}
	}
	free(masks);
	return count;
}


int* pre_kmp(char* needle, size_t needle_len){
	int* lps = malloc(sizeof(*lps) * needle_len);
	if(lps == NULL){
		printf("uh oh.\n");
		return lps;
	}
	memset(lps, 0, sizeof(*lps)*needle_len);
	int i = 1, j = 0;
	while(i < needle_len){
		if(*(needle+i) == *(needle+j)){
			*(lps+i) = ++j; 		
			i++;
		} else{
			if(j!=0){
				j = *(lps+j-1);
			} else{
				*(lps+i) = 0;
				i++;
			}
		}
	} 

	return lps;
}

int kmp(char* needle, char* haystack, size_t needle_len, size_t haystack_len){
	int* lps = pre_kmp(needle, needle_len);	
	int count = 0;
	int i = 0, j = 0;
	while(i < haystack_len){
		if(j==needle_len){
			count++;
			j = *(lps+j-1);
		}
		if(*(haystack+i) == *(needle+j)){
			j++;
			i++;
		} else{
			if(j!=0){
				j = *(lps+j-1);
			}else{
				i++;
			}
		}
	}

	return count;
}
