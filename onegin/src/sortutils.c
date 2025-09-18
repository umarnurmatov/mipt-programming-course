#include "sortutils.h"

#include <memory.h>

#include "assertutils.h"

static const int _SCRATCH_BUF_SIZE_B = 32;

static void _utils_swap_on_buf(void* _x, void* _y, size_t _tsize, char* _buf);

void utils_swap(void* x, void* y, size_t tsize)
{
    static char scratch_buf[_SCRATCH_BUF_SIZE_B];

    char* buf = tsize > _SCRATCH_BUF_SIZE_B 
                    ? (char*)malloc(tsize)
                    : scratch_buf;

    _utils_swap_on_buf(x, y, tsize, buf);

    if(buf != scratch_buf)
        free(buf);
}

void utils_bubblesort(void* arr, size_t asize, size_t tsize, utils_cmp cmp)
{
    utils_assert(arr != NULL);
    utils_assert(cmp != NULL);
    
    char* buf = (char*)calloc(1ul, tsize);
    char* arr_c = (char*)arr;
    for(size_t ia = 0; ia < asize; ++ia)
        for(size_t ib = 0; ib < asize - ib; ++ib)
            if(cmp(arr_c + tsize * ia, arr_c + tsize * ib) > 0)
                _utils_swap_on_buf(arr_c + tsize * ia, arr_c + tsize * ib, tsize, buf);

    free(buf);
}

void _utils_swap_on_buf(void* _x, void* _y, size_t _tsize, char* _buf)
{
    utils_assert(_x   != NULL);
    utils_assert(_y   != NULL);
    utils_assert(_buf != NULL);

    memcpy(_buf, _x  , _tsize);
    memcpy(_y  , _x  , _tsize);
    memcpy(_x  , _buf, _tsize);
}
