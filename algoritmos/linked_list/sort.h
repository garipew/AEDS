#ifndef SORT
#define SORT

#include "../../estruturas/linked_list/lista.h"
#include "../../estruturas/bin_tree/arvore_binaria.h"

int comparar_min(Item*, Item*);
int comparar_max(Item*, Item*);
void trocar_itens(Lista*, Item*, Item*);
void tornar_anterior(Lista*, Item*, Item*);
void insertion_sort(Lista*, int(*)(Item*, Item*));
void selection_sort(Lista*, int(*)(Item*, Item*));
void heap_sort(Lista*, int(*)(No*, No*));
#endif
