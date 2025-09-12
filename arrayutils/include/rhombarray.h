#pragma once

#include <stdlib.h>

#include "array.h"

typedef struct rhomb_array_t
{
    arr_data_t* ptr;
    size_t height;
} rhomb_array_t;

size_t utils_rhomb_array_get_size(rhomb_array_t* arr);

enum array_err_t utils_rhomb_array_init(rhomb_array_t* arr, size_t height);

enum array_err_t utils_rhomb_array_set(rhomb_array_t* arr, arr_data_t elem, size_t iy, size_t ix);

enum array_err_t utils_rhomb_array_get(rhomb_array_t* arr, arr_data_t* elem, size_t iy, size_t ix);

void utils_rhomb_array_free(rhomb_array_t* arr);

void utils_rhomb_array_print(rhomb_array_t* arr);