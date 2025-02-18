#ifndef MATCH_H
#define MATCH_H

#include <stddef.h>

int shift_and(const unsigned char*, const unsigned char*, size_t, size_t);
int kmp(const unsigned char*, const unsigned char*, size_t, size_t);
#endif
