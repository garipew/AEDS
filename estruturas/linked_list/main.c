#include "lista.h"
#include "../../algoritmos/linked_list/sort.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	Item* head = criar_item(NULL, 10);
	for(int i = 9; i > 0; i--){
		head = concat_item(head, criar_item(NULL, i));
	}

	printf("Original: ");
	escrever_lista(head);
	head = heap_sort(head, minimo);
	printf("Heap sort: ");
	escrever_lista(head);
	head = insertion_sort(head, comparar_max);
	printf("Insertion sort: ");
	escrever_lista(head);
	head = selection_sort(head, comparar_min);
	printf("Selection sort: ");
	escrever_lista(head);
	head = apagar_lista(head);
	return 0;
}
