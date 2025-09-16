#pragma once

/// @brief   swap strings using temporary buffer
/// @details swaps \p str_a and \p str_b contents using
///          user-provided temporary buffer \p str_tmp
void strswp_buffer(char* str_a, char* str_b, char* str_tmp);

/// @brief   swap strings char-by-char
void strswp_char(char* str_a, char* str_b);

/// @brief   swap strings chunk-by-chunk
/// @details swaps \p str_a and \p str_b contents
///          using 8-byte chunks
void strswp_chunks(char* str_a, char* str_b);
