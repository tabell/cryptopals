#include "hamming.h"

static inline int hot(
        uint8_t byte)
{
    int ret = 0;
    for (int b = 0; b < 8; b++)
    {
        ret += (byte & (1<<b)) >> b;
    }
    return ret;
}

int hamming(
        uint8_t *a,
        uint8_t *b,
        size_t len)
{
    int ret = 0;
    for (int i = 0; i < len; i++)
    {
        ret += hot(a[i] ^ b[i]);
    }
    return ret;
}

int hamming_test(void)
{
    char *inputs[] = { "this is a test", "wokka wokka!!!" };
    fprintf(stdout, "hamming distance = %d\n",
            hamming((unsigned char*)inputs[0], (unsigned char*)inputs[1],
                MAX(strlen(inputs[0]), strlen(inputs[1]))));
    return 0;
}



