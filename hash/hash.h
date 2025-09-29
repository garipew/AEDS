#ifndef HASH_H
#define HASH_H

#include "../linked_list/lista.h"
#define HASH_LIMIT 100

typedef struct hash{
	Lista** keys;
} Hash;


Hash* criar_hash();
Item* lookup(Hash*, const char*);
int install(Hash*, const char*);
unsigned hash(const char*);
void cleanup(Hash*);
void write_hash(Hash*);
#endif
