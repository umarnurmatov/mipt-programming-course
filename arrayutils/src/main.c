#include "trianglearray.h"
#include "logutils.h"

int main()
{
    utils_init_log("log.txt", "log");

    triangle_array_t arr; 
    utils_triangle_array_init(&arr, 5);
    
    utils_triangle_array_set(&arr, 5, 1, 0);

    utils_triangle_array_print(&arr);

    utils_triangle_array_free(&arr);

    utils_end_log(); 

    return 0;
}
