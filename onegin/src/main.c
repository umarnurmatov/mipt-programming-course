#include <stdio.h>
#include <getopt.h>

#include "fileline_arr.h"
#include "logutils.h"
#include "optutils.h"
#include "utils.h"
#include "sortutils.h"

static utils_long_opt_t long_opts[] = 
{
    { OPT_ARG_REQUIRED, "file", NULL, 0, 0 }
};

int main(int argc, char* argv[])
{
    utils_init_log("log.txt", "log");

    utils_long_opt_get(argc, argv, long_opts, SIZEOF(long_opts));
    if(!long_opts[0].is_set)
        return 1;

    FILE* file = open_file(long_opts[0].arg, "r");
    if(file == NULL)
        return 1;

    fileline_arr_t filearr = {
        .lcnt   = 0ul,
        .arr    = NULL,
        .buffer = NULL
    };

    fileline_arr_read(&filearr, file);
    fclose(file);

    fileline_arr_swap(&filearr, 0ul, 1ul);

    utils_bubblesort(filearr.arr, filearr.lcnt, sizeof(fileline_t), (utils_cmp)fileline_arr_linecmp);

    printf("%s\n", filearr.arr[0].str);

    fileline_arr_free(&filearr);

    utils_end_log();

    return 0;
}

