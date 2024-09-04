#ifndef SORT
#define SORT

#include "../../estruturas/linked_list/lista.h"

int comparar(Item*, Item*);
Item* trocar_itens(Item*, Item*, Item*);
Item* insertion_sort(Item*, int(*)(Item*, Item*));
Item* selection_sort(Item*, int(*)(Item*, Item*));
#endif
