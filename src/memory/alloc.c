#include "alloc.h"

#include <stdio.h>
#include <stdlib.h>


void *mem_alloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "mem_alloc(%lld): Out of memory\n", size);
        exit(1);
    }
    return ptr;
}


void *mem_realloc(void *ptr, size_t size) {
    void *tmp = realloc(ptr, size);
    if (tmp == NULL) {
        fprintf(stderr, "mem_realloc(ptr, %lld): No space found\n", size);
        exit(1);
    }
    return tmp;
}


void mem_free(void *ptr) {
    free(ptr);
}
