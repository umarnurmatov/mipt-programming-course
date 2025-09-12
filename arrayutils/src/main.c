#include "trianglearray.h"
#include "rhombarray.h"
#include "logutils.h"

int main()
{
    utils_init_log("log.txt", "log");

    triangle_array_t tarr; 
    utils_triangle_array_init(&tarr, 5);
    
    utils_triangle_array_set(&tarr, 5, 1, 0);

    utils_triangle_array_print(&tarr);

    utils_triangle_array_free(&tarr);

    rhomb_array_t rarr;
    utils_rhomb_array_init(&rarr, 5);
    
    utils_rhomb_array_print(&rarr);

    utils_rhomb_array_free(&rarr);

    utils_end_log(); 

    return 0;
}
