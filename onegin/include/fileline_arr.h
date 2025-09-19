#pragma once

#include "ioutils.h"

typedef struct fileline_t
{
    size_t len;
    size_t lnum;
    char* str;
} fileline_t;

typedef struct fineline_arr_t
{
    size_t lcnt;
    fileline_t* arr;
    char* buffer;
} fileline_arr_t;

typedef int(*fileline_arr_cmp_t)(fileline_t*, fileline_t*);

io_err_t fileline_arr_read(fileline_arr_t* filearr, FILE* stream);

fileline_t* fileline_arr_get(fileline_arr_t* filearr, size_t i);

void fileline_arr_swap(fileline_arr_t* filearr, size_t ia, size_t ib);

int fileline_arr_linecmp(fileline_t* line_a, fileline_t* line_b);

int fileline_arr_linercmp(fileline_t* line_a, fileline_t* line_b);

int fileline_arr_seqcmp(fileline_t* line_a, fileline_t* line_b);

io_err_t fileline_arr_put(fileline_arr_t* filearr, FILE* stream);

void fileline_arr_free(fileline_arr_t* filearr);

