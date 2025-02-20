#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "match.h"


unsigned long long* pre_shift_and(const unsigned char* needle, size_t needle_len){
	unsigned char size = ~0;
	unsigned long long *masks = malloc(sizeof(*masks)*(1+size));
	if(masks == NULL){
		printf("uh oh\n");
		return masks;
	}
	memset(masks, 0, sizeof(*masks)*(size+1));
	for(int i = 0; i < needle_len; i++){
		*(masks+*(needle+i)) += 1llu<<i;
	}
	return masks;
}


int shift_and(const unsigned char* needle, const unsigned char* haystack, size_t needle_len, size_t haystack_len){
	int count = 0;
	unsigned long long r = 0;
	unsigned long long* masks = pre_shift_and(needle, needle_len);
	if(masks == NULL){
		printf("uh oh\n");
		return count;
	}
	for(int i = 0; i < haystack_len; i++){
		r = ((r<<1) | 1llu) & *(masks +*(haystack+i));
		if(r & 1llu<<needle_len-1){
			count++;
		}
	}
	free(masks);
	return count;
}


int* pre_kmp(const unsigned char* needle, size_t needle_len){
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

int kmp(const unsigned char* needle, const unsigned char* haystack, size_t needle_len, size_t haystack_len){
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
