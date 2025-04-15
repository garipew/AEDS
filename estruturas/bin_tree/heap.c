#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


Heap* criar_heap(size_t len){
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


void inserir_heap(Heap* h, Item* data){
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


void heapfy(Heap* h, int idx, int (*comp)(Item*, Item*)){
	if(h->next < 2 || idx >= h->len){
		return;
	}
	int chosed = idx*2;
	Item* aux;
	if(chosed >= h->next){
		return;
	}
	if(chosed + 1 < h->next){
		chosed = comp(*(h->data+chosed), *(h->data+chosed+1)) ? chosed : chosed+1;
	}
	if(comp(*(h->data+chosed), *(h->data+idx))){
		aux = *(h->data+chosed);
		*(h->data+chosed) = *(h->data+idx);
		*(h->data+idx) = aux;
	}
}


void full_heapfy(Heap* h, int (*comp)(Item*, Item*)){
	int atual = ((h->next-1)/2);
	while(atual >= 0){
		heapfy(h, atual, comp);
		atual--;
	}
}


Item* remover_raiz(Heap* h){
	Item* aux;
	if(h->next > 1){
		aux = *(h->data);
		*(h->data) = *(h->data+h->next-1);
		*(h->data+h->next-1) = aux;
	}
	h->next--;
	return *(h->data+h->next);
}


void escrever_heap(Heap* h){
	for(int i = 0; i < h->next; i++){
		printf("%d ", *(h->data + i));
	}
	printf("\n");
}


void apagar_heap(Heap* h){
	if(h){
		if(h->data!=NULL){
			free(h->data);
		}
		free(h);
	}
}
