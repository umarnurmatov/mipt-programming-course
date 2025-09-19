#include <stdio.h>
#include <getopt.h>

#include "colorutils.h"
#include "fileline_arr.h"
#include "logutils.h"
#include "optutils.h"
#include "utils.h"
#include "sortutils.h"

static utils_long_opt_t long_opts[] = 
{
    { OPT_ARG_REQUIRED, "file", NULL, 0, 0 },
    { OPT_ARG_REQUIRED, "out",  NULL, 0, 0 }
};

int main(int argc, char* argv[])
{
    utils_init_log("log.txt", "log");

    utils_long_opt_get(argc, argv, long_opts, SIZEOF(long_opts));

    if(!long_opts[0].is_set) {
        utils_colored_fprintf(stderr, ANSI_COLOR_RED, "Specify input file\b");
        return 1;
    }

    if(!long_opts[1].is_set) {
        utils_colored_fprintf(stderr, ANSI_COLOR_RED, "Specify output file\n");
        return 1;
    }

    FILE* input_file = open_file(long_opts[0].arg, "r");
    if(input_file == NULL)
        return 1;

    fileline_arr_t filearr = {
        .lcnt   = 0ul,
        .arr    = NULL,
        .buffer = NULL
    };

    fileline_arr_read(&filearr, input_file);
    fclose(input_file);

    FILE* output_file = open_file(long_opts[1].arg, "a");
    if(input_file == NULL)
        return 1;

    utils_bubblesort(filearr.arr, filearr.lcnt, sizeof(filearr.arr[0]), (utils_cmp)fileline_arr_linecmp);
    fileline_arr_put(&filearr, output_file);
    
    // utils_bubblesort(filearr.arr, filearr.lcnt, sizeof(filearr.arr[0]), (utils_cmp)fileline_arr_linercmp);
    // fileline_arr_put(&filearr, output_file);
    
    utils_bubblesort(filearr.arr, filearr.lcnt, sizeof(filearr.arr[0]), (utils_cmp)fileline_arr_seqcmp);
    fileline_arr_put(&filearr, output_file);

    fclose(output_file);

    fileline_arr_free(&filearr);

    utils_end_log();

    return 0;
}

