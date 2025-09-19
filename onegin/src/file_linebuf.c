#include "file_linebuf.h"
#include "strswp.h"

io_err_t file_linebuf_read(file_linebuf_t* linebuf, FILE* stream)
{
    utils_assert(stream != NULL);
    utils_assert(linebuf != NULL);

    linebuf->buffer = (char*)calloc(linebuf->line_cnt, linebuf->line_len);
    
    if(linebuf->buffer == NULL)
        return IO_ERR_ALLOCATION_FAIL;

    for(size_t li = 0ul; li < linebuf->line_cnt; ++li)
    {
        char* line = file_linebuf_get(linebuf, li);
        if(utils_fgets(line, linebuf->line_cnt, stream) == NULL)
           break; 
    }

    return IO_ERR_NONE;
}

char* file_linebuf_get(file_linebuf_t* linebuf, size_t i)
{
    utils_assert(linebuf != NULL);
    utils_assert(i < linebuf->line_cnt);

    return linebuf->buffer + linebuf->line_len * i;
}

void file_linebuf_swap_buffer(file_linebuf_t* linebuf, size_t ia, size_t ib, char* str_tmp)
{
    utils_assert(linebuf != NULL);
    utils_assert(str_tmp != NULL);

    char* str_a = file_linebuf_get(linebuf, ia);
    char* str_b = file_linebuf_get(linebuf, ib);

    strswp_buffer(str_a, str_b, str_tmp);
}


void file_linebuf_swap_chunk(file_linebuf_t* linebuf, size_t ia, size_t ib)
{
    utils_assert(linebuf != NULL);

    char* str_a = file_linebuf_get(linebuf, ia);
    char* str_b = file_linebuf_get(linebuf, ib);

    strswp_chunks(str_a, str_b);
}

void file_linebuf_free(file_linebuf_t* linebuf)
{
    free(linebuf->buffer);
}

