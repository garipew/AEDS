#ifndef SORT
#define SORT

#include "../../estruturas/linked_list/lista.h"
#include "../../estruturas/bin_tree/arvore_binaria.h"

int comparar(Item*, Item*);
Item* trocar_itens(Item*, Item*, Item*);
Item* insertion_sort(Item*, int(*)(Item*, Item*));
Item* selection_sort(Item*, int(*)(Item*, Item*));
Item* heap_sort(Item*, int(*)(No*, No*));
#endif
