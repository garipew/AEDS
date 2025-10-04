#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

#define panic(msg) \
	perror(msg); \
	exit(1)

#define get_aligned_offset(offset, buff_type) \
	(((offset)+_Alignof(buff_type)-1) & ~(_Alignof(buff_type)-1))

Heap* criar_heap(int size){
	Heap* h;
	size_t total_size, nodes_offset;
	nodes_offset = get_aligned_offset(sizeof(*h), Pair*);
	total_size=nodes_offset+size*sizeof(*h->nodes);
	h = calloc(1, total_size);
	if(!h){
		panic("calloc fail");
	}
	h->nodes = (void*)((char*)h+nodes_offset);
	h->size = size;
	return h;
}

void print_heap(Heap* h){
	for(int i = 0; i < h->count; i++){
		printf("<%d %d> ", h->nodes[i].vertex, h->nodes[i].distance);
	}
	printf("\n");
}

void swap(Heap* h, int a, int b){
	h->nodes[a].distance = h->nodes[a].distance ^ h->nodes[b].distance;
	h->nodes[b].distance = h->nodes[a].distance ^ h->nodes[b].distance;
	h->nodes[a].distance = h->nodes[a].distance ^ h->nodes[b].distance;

	h->nodes[a].vertex = h->nodes[a].vertex ^ h->nodes[b].vertex;
	h->nodes[b].vertex = h->nodes[a].vertex ^ h->nodes[b].vertex;
	h->nodes[a].vertex = h->nodes[a].vertex ^ h->nodes[b].vertex;
}

void inserir_heap(Heap* h, int vertex, int dist){
	if(h->count >= h->size){
		fprintf(stderr, "full heap, can't insert.\n");
		return;
	}
	int idx = h->count;
	h->nodes[idx].distance = dist;
	h->nodes[idx].vertex = vertex;
	h->count++;

	int parent = (idx-1)/2;
	while(idx > 0 && h->nodes[idx].distance < h->nodes[parent].distance){
		swap(h, idx, parent);
		idx = parent;
		parent = (idx-1)/2;
	}
}

Pair remover_heap(Heap* h){
	Pair removed = {-1, -1};
	if(h->count == 0){
		fprintf(stderr, "empty heap, can't remove.\n");
		return removed;
	}
	removed = h->nodes[0];
	swap(h, h->count-1, 0);
	h->count--;
	int parent = 0;
	int min = parent;
	int left = min*2+1;
	int right = left+1;
	while(left < h->count){
		if(h->nodes[left].distance < h->nodes[min].distance){
			min = left;
		}
		if(right < h->count && h->nodes[right].distance < h->nodes[min].distance){
			min = right;
		}	
		if(min == parent){
			break;
		}
		swap(h, min, parent);
		parent = min;
		left = parent*2+1; 
		right = left+1;
	}
	return removed;
}

void heapfy(Heap* h){
	int n = h->count;
	int min, parent, left, right;
	for(int i = (n/2)-1; i >= 0; i--){
		parent = i;
		left = parent*2+1;
		right = left+1;
		while(left < n){
			min = parent;
			if(h->nodes[min].distance > h->nodes[left].distance){
				min = left;
			}
			if(right < n && h->nodes[min].distance > h->nodes[right].distance){
				min = right;
			}
			if(min == parent){
				break;
			}
			swap(h, min, parent);
			parent = min;
			left = parent*2+1;
			right = left+1;
		}
	}
}
