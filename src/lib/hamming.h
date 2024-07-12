#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

static inline int hot(
        uint8_t byte);

int hamming(
        uint8_t *a,
        uint8_t *b,
        size_t len);
