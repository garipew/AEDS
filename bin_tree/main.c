#include "arvore_binaria.h"
#include <stdlib.h>
#include <stdio.h>
/*
#include "heap.h"
#include "../../algoritmos/bin_tree/invert.h"
*/


int main(){
	No* raiz = criar_no(NULL, 0);
	for(int i = 1; i < 10; i++){
		inserir_bst(criar_no(NULL, i), raiz);
	}
	escrever_arvore(raiz);

	No* found = bin_search(raiz, 7);
	printf("%d\n", found->idx);

	apagar_arvore(raiz);
	return 0;
}
