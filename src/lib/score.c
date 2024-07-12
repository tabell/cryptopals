#include "score.h"

float score_sentence(
        float* charmap,
        unsigned char* text,
        size_t len)
{
    float total = 0;
    for (int i = 0; i < len; i++) {
        total += charmap[text[i]];
    }
    return (total / (float)len);
}

