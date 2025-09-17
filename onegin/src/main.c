#include <stdio.h>

#include "file_linebuf.h"
#include "fileline_arr.h"
#include "ioutils.h"

static const size_t strbuf_size    = 1000ul;
static const size_t onegin_linecnt = 7180ul;

int main()
{
    FILE* file = open_file("/home/n1njaeng1neer/source/mipt-programming-course/onegin/res/onegin.txt", "r");

    // file_linebuf_t linebuf = {
    //     onegin_linecnt,
    //     strbuf_size,
    //     NULL
    // };
    //
    // file_linebuf_read(&linebuf, file);
    //
    // char* tmp = (char*)calloc(1ul, linebuf.line_len);
    // file_linebuf_swap_buffer(&linebuf, 0ul, 1ul, tmp);
    //
    // printf("%s", file_linebuf_get(&linebuf, 0));
    // printf("%s", file_linebuf_get(&linebuf, 1));
    //
    // file_linebuf_swap_chunk(&linebuf, 0ul, 1ul);
    //
    // printf("%s", file_linebuf_get(&linebuf, 0));
    // printf("%s", file_linebuf_get(&linebuf, 1));
    //
    // file_linebuf_free(&linebuf);
    // free(tmp);


    fileline_arr_t filearr = {
        0ul,
        NULL
    };

    fileline_arr_read(&filearr, file);
    printf("%lu\n", filearr.lcnt);
    fileline_arr_swap(&filearr, 0ul, 1ul);

    fileline_arr_bubblesort(&filearr, fileline_arr_linecmp);

    for(size_t i = 0; i < filearr.lcnt; ++i)
        fprintf(stderr, "%s\n", fileline_arr_get(&filearr, i)->str);

    // qsort(filearr.arr, filearr.lcnt, sizeof(filearr.arr[0]), fileline_arr_linecmp);
    //
    fileline_arr_free(&filearr);

    fclose(file);
    return 0;
}

