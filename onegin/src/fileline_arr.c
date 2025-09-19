#include "fileline_arr.h"

#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "ioutils.h"
#include "logutils.h"
#include "memutils.h"
#include "stringutils.h"

io_err_t fileline_arr_read(fileline_arr_t* filearr, FILE* stream)
{
    utils_assert(filearr != NULL);
    utils_assert(stream  != NULL);

    size_t file_size_b = get_file_size(stream);
    char* buffer = (char*)calloc(1ul, file_size_b + 1ul);
    if(buffer == NULL) {
        utils_log(
            LOG_LEVEL_ERR, 
            "failed to allocate memory"
        );
        return IO_ERR_ALLOCATION_FAIL;
    }

    size_t bytes_read = fread(buffer, sizeof(buffer[0]), file_size_b, stream);
    if(bytes_read < file_size_b) {
        utils_log(
            LOG_LEVEL_ERR, 
            "failed to read file"
        );
        return IO_ERR_EOF_REACHED;
    }

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
    utils_assert(line_a != NULL);
    utils_assert(line_b != NULL);

    size_t line_a_len = utils_strlen(line_a->str);
    size_t line_b_len = utils_strlen(line_b->str);

    char* str_a = line_a->str;
    char* str_b = line_b->str;

    char* str_a_ptr = str_a + line_a_len;
    char* str_b_ptr = str_b + line_b_len;

    while((str_a_ptr != str_a) || (str_b_ptr != str_b))
    {
        --str_a_ptr;
        --str_b_ptr;

        if(!isalpha(*str_a_ptr) || !isalpha(*str_b_ptr))
            continue;

        if(*str_a_ptr > *str_b_ptr)
            return 1;
        else if(*str_a_ptr < *str_b_ptr)
            return -1;
    }

    return 0;
}

int fileline_arr_seqcmp(fileline_t* line_a, fileline_t* line_b)
{
    utils_assert(line_a != NULL);
    utils_assert(line_b != NULL);

    return line_a->lnum > line_b->lnum;
}

io_err_t fileline_arr_put(fileline_arr_t* filearr, FILE* stream)
{
    for(size_t li = 0ul; li < filearr->lcnt; ++li)
    {
        if(fprintf(stream, "%s\n", filearr->arr[li].str) < 0) {
            utils_log(
                LOG_LEVEL_ERR, 
                "file write error"
            );
            return IO_ERR_EOF_REACHED;
        }
    }

    return IO_ERR_NONE;
}

void fileline_arr_free(fileline_arr_t* filearr)
{
    utils_assert(filearr         != NULL);
    utils_assert(filearr->buffer != NULL);
    utils_assert(filearr->arr    != NULL);

    nfree(filearr->buffer);
    nfree(filearr->arr);
}

