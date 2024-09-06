#include "lista.h"
#include "../../algoritmos/linked_list/sort.h"
#include <stdlib.h>
#include <stdio.h>


int main(){
	Item* head = criar_item(NULL, 0);
	for(int i = 1; i < 1000; i++){
		head = concat_item(head, criar_item(NULL, i));
		head = concat_item(head, criar_item(NULL, 1000 - i));
	}

	escrever_lista(head);

	head = heap_sort(head, minimo);
	printf("Heap sort: ");
	escrever_lista(head);

	head = insertion_sort(head, comparar_max);
	printf("Insertion sort: ");
	escrever_lista(head);

	head = selection_sort(head, comparar_max);
	printf("Selection sort: ");
	escrever_lista(head);
	head = apagar_lista(head);
	return 0;
}
