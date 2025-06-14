#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <stdint.h>


void *mem_alloc(size_t size);
void *mem_realloc(void *ptr, size_t size);
void mem_free(void *ptr);


#endif  // __ALLOC_H__
