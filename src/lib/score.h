#include <ctype.h>
#include <stdlib.h>
#include "list.h"

typedef struct score {
    list_node_t node; /* must be first member for casting */
    unsigned char key;
    float score;
    char *ct;
} score_t;

float score_sentence(
        float* charmap,
        unsigned char* text,
        size_t len);

