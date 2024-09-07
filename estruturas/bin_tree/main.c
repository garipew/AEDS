#include "arvore_binaria.h"
#include "../../algoritmos/bin_tree/invert.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	Lista* heap = criar_lista();
	/*
	No *a, *b;
	a = criar_no(NULL, 30);
	b = criar_no(NULL, 79);
	inserir_nivel(heap, b);
	*/
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
	return 0;
}
