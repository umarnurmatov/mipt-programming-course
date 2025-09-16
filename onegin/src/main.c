#include <stdio.h>

#include "file_linebuf.h"
#include "file_strbuf.h"
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


    file_strbuf_t strbuf = {
        onegin_linecnt,
        NULL
    };

    file_strbuf_read(&strbuf, file);
    file_strbuf_swap(&strbuf, 0ul, 1ul);
    printf("%s", file_strbuf_get(&strbuf, 0));
    printf("%s", file_strbuf_get(&strbuf, 1));
    file_strbuf_free(&strbuf);

    fclose(file);
    return 0;
}

