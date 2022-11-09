#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int compareInt(Type, Type);

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    int g = 7;
    Set set = createSet(compareInt, sizeof(int));
    printf("Add 1: %d\n", addSet(set, &a));
    printf("Size: %d\n", sizeSet(set));
    printf("Add 2: %d\n", addSet(set, &b));
    printf("Size: %d\n", sizeSet(set));
    printf("Add 3: %d\n", addSet(set, &c));
    printf("Size: %d\n", sizeSet(set));
    printf("Add 4: %d\n", addSet(set, &d));
    printf("Size: %d\n", sizeSet(set));
    printf("Add 5: %d\n", addSet(set, &e));
    printf("Size: %d\n", sizeSet(set));
    printf("Does it contain 1? %d\n", containSet(set, &a));
    printf("Does it contain 3? %d\n", containSet(set, &c));
    printf("Does it contain 7? %d\n", containSet(set, &g));
    printf("Remove 2: %d\n", removeSet(set, &b));
    printf("Size: %d\n", sizeSet(set));
    printf("Does it contain 2? %d\n", containSet(set, &b));
    return 0;
}

int compareInt(Type a, Type b) {
    int *a1 = a;
    int *b1 = b;
    if (*a1 < *b1) {
        return -1;
    }
    if (*a1 > *b1) {
        return 1;
    }
    if (*a1 == *b1) {
        return 0;
    }
    return 0;
}