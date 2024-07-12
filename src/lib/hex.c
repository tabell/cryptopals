#include <stdio.h>
#include <stdlib.h>
#include "base64.h"

int hex_to_b64(
        const unsigned char *hex,
        unsigned char *b64)
{
    uint8_t in[3];
    int ret;
    /* read hex 8 "bytes" at a time and convert to uint32 */
    while (0 < (ret = sscanf((const char *)hex, "%2hhx%2hhx%2hhx",  &in[0], &in[1], &in[2]))) {
        b64_enc(in, ret, b64);
        hex += 2*ret;
        b64 += ret + 1;
    }
    *b64 = '\0';

    return 0;
}
