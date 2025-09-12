#include "rhombarray.h"

#include <stdio.h>
#include <memory.h>

#include "logutils.h"
#include "assertutils.h"

int _utils_is_odd(size_t x);
void _putnchar(char c, size_t n, FILE* stream);

static arr_data_t* _utils_rhomb_array_get_ptr(rhomb_array_t* arr, size_t iy, size_t ix);
static size_t _utils_rhomb_get_row_len(rhomb_array_t* arr, size_t iy);

size_t utils_rhomb_array_get_size(rhomb_array_t* arr)
{
    size_t half_height = arr->height / 2ul;

    if(_utils_is_odd(arr->height))
        return 2 * half_height * half_height + arr->height;
    else
        return 2 * half_height * half_height;
}

enum array_err_t utils_rhomb_array_init(rhomb_array_t* arr, size_t height)
{
    utils_assert(arr != NULL);

    arr->height = height;
    size_t arr_size = utils_rhomb_array_get_size(arr);

    arr->ptr = (arr_data_t*)calloc(arr_size, sizeof(arr_data_t));
    if(arr->ptr == NULL) {
        utils_log(LOG_LEVEL_ERR, "failed to allocate array");
        return ARRAY_ERR_ALLOCATION_FAILED;
    }

    return ARRAY_ERR_NONE;
}

enum array_err_t utils_rhomb_array_set(rhomb_array_t* arr, arr_data_t elem, size_t iy, size_t ix)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);

    arr_data_t* ptr = _utils_rhomb_array_get_ptr(arr, iy, ix);
    if(ptr == NULL)
        return ARRAY_ERR_OUT_OF_RANGE;

    *ptr = elem;

    return ARRAY_ERR_NONE;
}

enum array_err_t utils_rhomb_array_get(rhomb_array_t* arr, arr_data_t* elem, size_t iy, size_t ix)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);

    arr_data_t* ptr = _utils_rhomb_array_get_ptr(arr, iy, ix);
    if(ptr == NULL)
        return ARRAY_ERR_OUT_OF_RANGE;

    *elem = *ptr;

    return ARRAY_ERR_NONE;
}

void utils_rhomb_array_free(rhomb_array_t* arr)
{
    free(arr->ptr);
    arr->ptr = NULL;
}

static arr_data_t *_utils_rhomb_array_get_ptr(rhomb_array_t *arr, size_t iy, size_t ix)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);

    if(ix >= _utils_rhomb_get_row_len(arr, iy) || iy >= arr->height) {
        utils_log(LOG_LEVEL_ERR, "index out of range");
        return NULL;
    }

    size_t half_height = arr->height / 2ul;
    size_t is_odd      = (size_t)_utils_is_odd(arr->height);
    size_t offset      = 0ul;
    if(iy < half_height)
        offset = ix + iy * iy;
    else
        offset = ix + half_height            * half_height 
                    + (half_height + is_odd) * (half_height + is_odd)
                    - (arr->height - iy)     * (arr->height - iy);

    return (arr_data_t*)((size_t)arr->ptr + offset * sizeof(arr_data_t));
}

void utils_rhomb_array_print(rhomb_array_t* arr)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);

    for(size_t iy = 0; iy < arr->height; ++iy) {
        size_t row_size = _utils_rhomb_get_row_len(arr, iy);
        _putnchar('\t', (arr->height - row_size) / 2ul, stdout);

        for(size_t ix = 0ul; ix < row_size; ++ix)
            printf("%d\t", iy, ix, *_utils_rhomb_array_get_ptr(arr, iy, ix));

        putc('\n', stdout);
    }
}

size_t _utils_rhomb_get_row_len(rhomb_array_t* arr, size_t iy)
{
    size_t half_height = arr->height / 2ul;

    if(iy < half_height)
        return 2ul * iy + 1ul;
    else
        return 2ul * (arr->height - iy) - 1ul;
}

int _utils_is_odd(size_t x)
{
    return x % 2ul == 1ul;
}

void _putnchar(char c, size_t n, FILE* stream)
{
    for(size_t i = 0; i < n; ++i)
        putc(c, stream);
}
