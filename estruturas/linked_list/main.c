#include "lista.h"
#include "../../algoritmos/linked_list/sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int stoi(char* string);


int main(int argc, char* argv[]){
	srand(time(NULL));
	int wid, hei;
	wid = argc >= 2 ? stoi(argv[1]) : 100;
	hei = argc >= 3 ? stoi(argv[2]) : 10000;
	Item* head = criar_item(NULL, rand()%hei);
	for(int i = 1; i < wid; i++){
		head = concat_item(head, criar_item(NULL, rand()%hei));
	}

	escrever_lista(head);

	head = heap_sort(head, minimo);
	printf("Heap sort: ");
	escrever_lista(head);

	/*
	head = insertion_sort(head, comparar_min);
	printf("Insertion sort: ");
	escrever_lista(head);

	head = selection_sort(head, comparar_min);
	printf("Selection sort: ");
	escrever_lista(head);
	*/
	head = apagar_lista(head);
	return 0;
}


/* stoi(char*)
 * string to int, recebe uma string e retorna o valor int presente
 */
int stoi(char* string){
	int num = 0;	
	for(int i = 0; i < strlen(string); i++){
		num = num * 10 + (string[i] - '0');
	}
	return num;
}
