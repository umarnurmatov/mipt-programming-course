#include "fileline_arr.h"

#include <string.h>
#include <stdint.h>

#include "logutils.h"

io_err_t fileline_arr_read(fileline_arr_t* filearr, FILE* stream)
{
    size_t file_size_b = get_file_size(stream);
    char* buffer = (char*)calloc(1ul, file_size_b);
    if(buffer == NULL) {
        utils_log(
            LOG_LEVEL_ERR, 
            "failed to allocate memory"
        );
        return IO_ERR_ALLOCATION_FAIL;
    }

    fread(buffer, sizeof(buffer[0]), file_size_b, stream);

    // count lines except blank
    // because of strtok()
    size_t lcnt = 0ul;
    char buffer_c_prev = '\n', buffer_c_curr = '\n';
    for(size_t bi = 0ul; bi < file_size_b; ++bi) {
        buffer_c_curr = buffer[bi];
        if(buffer_c_curr == '\n' && buffer_c_prev != '\n')
            ++lcnt;
        buffer_c_prev = buffer_c_curr;
    }

    filearr->arr = 
        (fileline_t*)calloc(lcnt, sizeof(filearr->arr[0]));
    if(buffer == NULL) {
        utils_log(
            LOG_LEVEL_ERR, 
            "failed to allocate memory"
        );
        return IO_ERR_ALLOCATION_FAIL;
    }
    filearr->lcnt = lcnt;
    filearr->buffer = buffer;

    lcnt = 0ul;
    char* line = strtok(filearr->buffer, "\n");
    while(line) {
        filearr->arr[lcnt].str = line;
        filearr->arr[lcnt].lnum = lcnt;
        line = strtok(NULL, "\n");
        filearr->arr[lcnt].len = 
            (size_t)(line - filearr->arr[lcnt].str);
        ++lcnt;
    }

    return IO_ERR_NONE;
}

fileline_t* fileline_arr_get(fileline_arr_t* filearr, size_t i)
{
    utils_assert(filearr != NULL);
    utils_assert(i < filearr->lcnt);

    return filearr->arr + i;
}

void fileline_arr_swap(fileline_arr_t* filearr, size_t ia, size_t ib)
{
    utils_assert(filearr != NULL);
    utils_assert(ia < filearr->lcnt);
    utils_assert(ib < filearr->lcnt);

    fileline_t tmp_line = filearr->arr[ia];
    filearr->arr[ia]    = filearr->arr[ib];
    filearr->arr[ib]    = tmp_line;
}

int fileline_arr_linecmp(fileline_t* line_a, fileline_t* line_b)
{
    utils_assert(line_a != NULL);
    utils_assert(line_b != NULL);

    return strcmp(line_a->str, line_b->str);
}


int fileline_arr_linercmp(fileline_t* line_a, fileline_t* line_b)
{
    return -1 * fileline_arr_linecmp(line_a, line_b);
}


void fileline_arr_bubblesort(fileline_arr_t* filearr, fileline_arr_cmp_t cmp)
{
    utils_assert(filearr != NULL);

    for(size_t ia = 0ul; ia < filearr->lcnt; ++ia)
        for(size_t ib = ia; ib < filearr->lcnt; ++ib)
            if(cmp(fileline_arr_get(filearr, ia), fileline_arr_get(filearr, ib)) > 0)
                fileline_arr_swap(filearr, ia, ib);
}

void fileline_arr_free(fileline_arr_t* filearr)
{
    utils_assert(filearr         != NULL);
    utils_assert(filearr->buffer != NULL);
    utils_assert(filearr->arr    != NULL);

    free(filearr->buffer);
    free(filearr->arr);
}


