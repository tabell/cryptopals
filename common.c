#include <ctype.h>
#include "common.h"

void bytes_to_hex(
        uint8_t *in,
        size_t in_len,
        unsigned char* out)
{
    for (size_t off = 0; off < in_len; off++) {
        snprintf(out+(2*off), 3, "%2x", *(in+off));
    }
}
void hex_to_bytes(
        unsigned char *in,
        uint8_t *out)
{
    int ret = 0;
    size_t offset = 0;
    while (0 < sscanf(in + offset*2, "%2hhx", out + offset))
    {
        offset++;
    }
}

void xor(
        uint8_t *a,
        uint8_t *b,
        uint8_t *out,
        size_t len)
{
    for (int x = 0; x < len; x++) {
        out[x] = a[x] ^ b[x];
    }
}

float score(
        char* text,
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

