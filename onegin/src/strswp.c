#include "strswp.h"

#include <stdint.h>
#include <memory.h>

#include "assertutils.h"
#include "stringutils.h"

void strswp_buffer(char* str_a, char* str_b, char* str_tmp)
{
    utils_assert(str_a != NULL);
    utils_assert(str_b != NULL);

    utils_strcpy(str_tmp, str_a);
    utils_strcpy(str_a, str_b);
    utils_strcpy(str_b, str_tmp);
}

void strswp_char(char* str_a, char* str_b)
{
    utils_assert(str_a != NULL);
    utils_assert(str_b != NULL);
    
    char* str_a_char = str_a;
    char* str_b_char = str_b;
    char tmp;

    while(*str_a_char != '\0')
    {
        tmp = *str_a_char;
        *str_a_char = *str_b_char;
        *str_b_char = tmp;

        ++str_a_char;
        ++str_b_char;
    }
}

void strswp_chunks(char* str_a, char* str_b)
{
    utils_assert(str_a != NULL);
    utils_assert(str_b != NULL);

    size_t  str_len = utils_strlen(str_a);
    size_t  str_i   = 0ul;
    int64_t buf     = 0l;

    for( ; str_i < str_len; ++str_i) {
        if(str_i + sizeof(int64_t) >= str_len)
            break;

        memcpy(&buf,          str_a + str_i, sizeof(int64_t));
        memcpy(str_a + str_i, str_b + str_i, sizeof(int64_t));
        memcpy(str_b + str_i, &buf         , sizeof(int64_t));
    }

    strswp_char(str_a + str_i, str_b + str_i);
}

