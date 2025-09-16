#pragma once

#include "ioutils.h"

typedef struct file_linebuf_t
{
    size_t line_cnt;
    size_t line_len;
    char* buffer;
} file_linebuf_t;

io_err_t file_linebuf_read(file_linebuf_t* linebuf, FILE* stream);

char* file_linebuf_get(file_linebuf_t* linebuf, size_t i);

void file_linebuf_swap_buffer(file_linebuf_t* linebuf, size_t ia, size_t ib, char* str_tmp);

void file_linebuf_swap_chunk(file_linebuf_t* linebuf, size_t ia, size_t ib);

void file_linebuf_free(file_linebuf_t* linebuf);

