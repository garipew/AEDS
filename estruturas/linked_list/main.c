#include "lista.h"
#include "../../algoritmos/linked_list/sort.h"
#include <stdlib.h>


int main(){
	Item* head = criar_item(NULL, 10);
	for(int i = 9; i > 0; i--){
		head = insertion_sort(head, criar_item(NULL, i), comparar);
	}

	head = apagar_lista(head);
	return 0;
}
