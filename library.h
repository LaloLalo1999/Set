#ifndef SET_LIBRARY_H
#define SET_LIBRARY_H

#include <stddef.h>

typedef enum {false, true} bool;

typedef void * Type;

typedef int(*Compare)(Type, Type);

typedef struct Set * Set;

Set createSet(Compare, size_t);

int sizeSet(Set);

bool addSet(Set, Type);

bool containSet(Set, Type);

bool removeSet(Set, Type);

void destroySet(Set);

#endif //SET_LIBRARY_H
