//#include "arvore_binaria.h"
//#include "../../algoritmos/bin_tree/invert.h"
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


int main(){
	/*
	Lista* heap = criar_lista();
	No *a, *b;
	a = criar_no(NULL, 30);
	b = criar_no(NULL, 79);
	inserir_nivel(heap, b);
	for(int i = 9; i > 0; i--){
		inserir_nivel(heap, criar_no(NULL, i));
	}

	escrever_lista(heap);
	full_heapfy(heap, minimo);
	escrever_lista(heap);
	while(heap->primeiro != heap->ultimo){
		remover_heap(heap, minimo);
		escrever_lista(heap);
	}
	apagar_lista(heap);
	*/
	Heap* heap = criar_heapy(30);
	for(int i = 10; i > 0; i--){
		inserir_heapy(heap, i);
	}
	full_heapyfy(heap, min_heap);
	escrever_heapy(heap);
	while(heapy->next > 0){
		printf("%d era o menor elemento da heap.\n", remover_raiz(heap));
		full_heapyfy(heap, min_heap);
	}

	apagar_heapy(heap);
	
	return 0;
}
