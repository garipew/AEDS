#include "lista.h"
#include "../../algoritmos/linked_list/sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int stoi(char* string);


int main(int argc, char* argv[]){
	srand(time(NULL));
	Lista* l = criar_lista();
	int wid, hei;
	wid = argc >= 2 ? stoi(argv[1]) : 100;
	hei = argc >= 3 ? stoi(argv[2]) : 10000;
	for(int i = 1; i < wid; i++){
		concat_item(l, criar_item(NULL, rand()%hei));
		//concat_item(l, criar_item(NULL, i));
	}

	escrever_lista(l);
	heap_sort(l, maximo);
	printf("Heap sort: ");
	escrever_lista(l);
	/*
	insertion_sort(l, comparar_min);
	printf("Insertion sort: ");
	escrever_lista(l);

	selection_sort(l, comparar_max);
	printf("Selection sort: ");
	escrever_lista(l);
	*/
	apagar_lista(l);
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
