#pragma once

#include "ioutils.h"

typedef struct file_strbuf_t
{
    size_t line_cnt;
    char** buffer;
} file_strbuf_t;

io_err_t file_strbuf_read(file_strbuf_t* strbuf, FILE* stream);

char* file_strbuf_get(file_strbuf_t* strbuf, size_t i);

void file_strbuf_swap(file_strbuf_t* strbuf, size_t ia, size_t ib);

void file_strbuf_free(file_strbuf_t* strbuf);

