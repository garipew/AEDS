#ifndef SORT
#define SORT

#include "../../estruturas/linked_list/lista.h"

int comparar(Item*, Item*);
Item* insertion_sort(Item*, Item*, int(*)(Item*, Item*));
#endif
