#include "score.h"

float score_sentence(
        unsigned char* text,
        size_t len)
{
    float total = 0;
    for (int i = 0; i < len; i++) {
        total += (isalnum(text[i]) ? 1 : 0);
        total += (isspace(text[i]) ? 1 : 0);
        total += (iscntrl(text[i]) ? -5 : 0);
        total += (ispunct(text[i]) ? -1 : 0);

    }
    return (total / (float)len);
}

