#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


Heap* criar_heapy(size_t len){
	Heap* h = malloc(sizeof(*h));
	if(h==NULL){
		printf("uh oh.\n");
		return h;
	}
	h->data = malloc(sizeof(*(h->data))*len);
	if(h->data==NULL){
		printf("uh oh.\n");
		free(h);
		return NULL;
	}
	h->len = len;
	h->next = 0;
	return h;
}


void inserir_heapy(Heap* h, int data){
	if(h->len <= h->next){
		printf("Heap is full...\n");
		return;
	}
	*(h->data+h->next) = data;	
	h->next++;
}


int min_heap(int a, int b){
	return a < b;
}


int max_heap(int a, int b){
	return a > b;
}


void heapyfy(Heap* h, int idx, int (*comp)(int, int)){
	if(h->next < 2 || idx >= h->len){
		return;
	}
	int chosed = idx*2;
	if(chosed >= h->next){
		return;
	}
	if(chosed + 1 < h->next){
		chosed = comp(*(h->data+chosed), *(h->data+chosed+1)) ? chosed : chosed+1;
	}
	if(comp(*(h->data+chosed), *(h->data+idx))){
		*(h->data+chosed) ^= *(h->data+idx);
		*(h->data+idx) ^= *(h->data+chosed);
		*(h->data+chosed) ^= *(h->data+idx);
	}
}


void full_heapyfy(Heap* h, int (*comp)(int, int)){
	int atual = ((h->next-1)/2);
	while(atual >= 0){
		heapyfy(h, atual, comp);
		atual--;
	}
}


int remover_raiz(Heap* h){
	if(h->next > 1){
		*(h->data) ^= *(h->data+h->next-1);
		*(h->data+h->next-1) ^= *(h->data);
		*(h->data) ^= *(h->data+h->next-1);
	}
	h->next--;
	return *(h->data+h->next);
}


void escrever_heapy(Heap* h){
	for(int i = 0; i < h->next; i++){
		printf("%d ", *(h->data + i));
	}
	printf("\n");
}


void apagar_heapy(Heap* h){
	if(h){
		if(h->data!=NULL){
			free(h->data);
		}
		free(h);
	}
}
