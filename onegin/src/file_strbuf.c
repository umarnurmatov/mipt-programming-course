#include "file_strbuf.h"

#include <string.h>

io_err_t file_strbuf_read(file_strbuf_t* strbuf, FILE* stream)
{
    strbuf->buffer = (char**)calloc(strbuf->line_cnt, sizeof(char*));

    size_t  line_size    = 0ul;
    ssize_t char_written = 0l;

    for(size_t i = 0; i < strbuf->line_cnt; ++i)
    {
        char* line = NULL;
        utils_getline(&line, &line_size, stream, &char_written);
        strbuf->buffer[i] = line;
    }

    return IO_ERR_NONE;
}

char* file_strbuf_get(file_strbuf_t* strbuf, size_t i)
{
    utils_assert(strbuf != NULL);

    return strbuf->buffer[i];
}

void file_strbuf_swap(file_strbuf_t* strbuf, size_t ia, size_t ib)
{
    utils_assert(strbuf != NULL);
    utils_assert(ia < strbuf->line_cnt);
    utils_assert(ib < strbuf->line_cnt);

    char* tmp_ptr = strbuf->buffer[ia];
    strbuf->buffer[ia] = strbuf->buffer[ib];
    strbuf->buffer[ib] = tmp_ptr;
}

void file_strbuf_free(file_strbuf_t* strbuf)
{
    utils_assert(strbuf != NULL);

    for(size_t i = 0ul; i < strbuf->line_cnt; ++i)
        free(strbuf->buffer[i]);

    free(strbuf->buffer);
    strbuf->buffer = NULL;
}
