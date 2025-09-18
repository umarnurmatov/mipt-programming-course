#pragma once

#include <stdlib.h>

typedef int (*utils_cmp)(void*,void*);

void utils_swap(void* x, void* y, size_t tsize);

void utils_bubblesort(void* arr, size_t asize, size_t tsize, utils_cmp cmp);
