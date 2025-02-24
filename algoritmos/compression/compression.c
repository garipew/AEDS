#include "compression.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


No** encontrar_alfabeto(const unsigned char* str, size_t str_len){
	const unsigned int size = 0x100;
	unsigned char* frequency = malloc(sizeof(*frequency)*(size));
	No** frequency_tree = malloc(sizeof(*frequency_tree)*str_len);
	int elements = 0;
	memset(frequency, 0, sizeof(*frequency)*(size));
	memset(frequency_tree, 0, sizeof(*frequency_tree)*(str_len));
	for(int i = 0; i < str_len; i++){
		*(frequency+*(str+i))+=1;
	}
	for(int i = 0; i < size; i++){
		if(*(frequency+i) == 0){
			continue;
		}
		*(frequency_tree+elements) = criar_no(criar_no(NULL, i), *(frequency+i));
		elements++;
	}
	free(frequency);
	return frequency_tree;
}


int contar_elementos(No** array, size_t array_size){
	int count;
	for(count = 0; count < array_size; count++){
		if(*(array+count) == NULL){
			break;
		}
	}
	return count;
}


int encontrar_menor(No** array, size_t array_size){
	if(*array == NULL){
		return -1;
	}
	No* menor = *array;
	int menor_idx = 0;
	for(int i = 1; i < array_size; i++){
		if(*(array+i) == NULL){
			break;
		}
		if(menor->idx > (*(array+i))->idx){
			menor = *(array+i);
			menor_idx = i;	
		}
		
	}
	return menor_idx;
}


void mover_no(No** array, size_t array_size, int idx){
	if(idx < 0 || idx >= array_size || array_size <= 1 || idx == (array_size - 1)){
		return;
	}
	No* aux = *(array+(array_size-1));
	*(array+(array_size-1)) = *(array+idx);
	*(array+idx) = aux;
}


void print_array(No** array, size_t array_size){
	for(int i = 0; i < array_size; i++){
		if(*(array+i) == NULL){
			break;
		}
		if((No*)((*(array+i))->dado) != NULL){
			printf("%c %d\n", ((No*)((*(array+i))->dado))->idx, (*(array+i))->idx);
		}
	}
	printf("\n");
}


void juntar_menores(No** array, size_t array_len){
	No *a, *b;
	int a_idx = encontrar_menor(array, array_len), b_idx;
	if(a_idx < 0){
		return;
	}
	mover_no(array, array_len, a_idx);
	a = *(array+(array_len-1));
	array_len--;
	b_idx = encontrar_menor(array, array_len);
	if(b_idx < 0){
		return;
	}
	mover_no(array, array_len, b_idx);
	b = *(array+(array_len-1));
	*(array+(array_len-1)) = juntar_nos(a, b);
	*(array+(array_len)) = NULL;
}


void pre_huffman(const No* raiz, unsigned long long mask, unsigned long long* dict, size_t dict_len, unsigned long long current_bit){
	if(raiz == NULL){
		return;
	}
	if(raiz->dado != NULL){
		*(dict+((No*)raiz->dado)->idx) = mask;	
	}
	pre_huffman(raiz->esq, mask+(1llu<<current_bit), dict, dict_len, current_bit+1);	
	pre_huffman(raiz->dir, mask, dict, dict_len, current_bit+1);	
}


unsigned long long* criar_dicionario(const No* raiz){
	if(raiz == NULL){
		return NULL;
	}
	const int size = 0x100; // range to accomodate all possible characters
	unsigned long long* dict = malloc(sizeof(*dict)*size);
	if(dict == NULL){
		return NULL;
	}
	memset(dict, 0, sizeof(*dict)*size);
	unsigned long long mask = 0;
	pre_huffman(raiz, mask, dict, size, 0ull);
	return dict;
}


int encontrar_letra(No* tree, unsigned long long mask, int print){
	No* raiz = tree;
	unsigned long long current_bit = 0;
	int bits_necessarios = 0;	
	while((raiz != NULL) && (raiz->dado == NULL)){
		if((mask & 1llu<<(current_bit)) > 0llu){
			raiz = raiz->esq;
		} else{
			raiz = raiz->dir;
		}
		current_bit++;
		bits_necessarios++;
	}
	if((raiz->dado != NULL) && print){
		printf("%c", ((No*)(raiz->dado))->idx);
	}
	return bits_necessarios;
}


void print_bits(unsigned long long sequence){
	char* ptr = (char*)&sequence;
	for(int i = 0; i < sizeof(sequence); i++){
		printf("%c", *(ptr+i));	
	}
}


void huffman_coding(const unsigned char* str, size_t str_len){
	No** frequency_array = encontrar_alfabeto(str, str_len);
	int elementos = contar_elementos(frequency_array, str_len);
	print_array(frequency_array, elementos);
	for(int i = elementos; i > 1; i--){
		juntar_menores(frequency_array, i);
	}
	No* frequency_tree = *(frequency_array);
	unsigned long long* dict = criar_dicionario(frequency_tree);
	unsigned long long sequence = 0, resto = 0;
	unsigned int bits_usados = 0, bits_necessarios = 0;
	for(int i = 0; i < str_len; i++){
		bits_necessarios=encontrar_letra(frequency_tree, *(dict+*(str+i)), 0);
		if((bits_usados + bits_necessarios) >= (sizeof(sequence)*8)){
			sequence+=(*(dict+*(str+i)))<<bits_usados;
			resto=(*(dict+*(str+i)))>>(bits_usados+bits_necessarios-(sizeof(sequence)*8));
			print_bits(sequence);
			bits_usados+=bits_necessarios-(sizeof(sequence)*8);
			sequence=resto;
			continue;
		}
		sequence+=(*(dict+*(str+i)))<<bits_usados;
		bits_usados+=bits_necessarios;
	}
	apagar_arvore_full(frequency_tree);
	free(frequency_array);
	free(dict);
}


void huffman_decoding(const unsigned char* str, size_t str_len){
	// Ler e construir arvore de frequencia, arvore acaba com \n\n
	
	/* Ler cada unsigned char do arquivo, percorrer a arvore e printar cada char
	 * levar em consideração que cada caractere do arquivo pode estar armazenando
	 * varios caracteres na arvore, ou as vezes até 1,5 caracteres por exemplo...
	*/
}
