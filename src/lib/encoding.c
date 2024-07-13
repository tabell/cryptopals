#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* Base64 in a nutshell:
 * aaaaaaaa bbbbbbbb cccccccc 
 * aaaaaa aa bbbb bbbb cc cccccc 
 * aaaaaa aabbbb bbbbcc cccccc 
 * aaaaaa     aabbbb   bbbbcc   cccccc 
 * 00aaaaaa 00aabbbb 00bbbbcc 00cccccc 
 */

#define B64_LOOKUP "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

int b64_enc(
	unsigned char *input,
    size_t in_len,
	unsigned char *output)
{
    int whole_groups = in_len / 3;
    int remaining_groups = in_len % 3;
    uint8_t out[4];

    for (int x = 0; x < whole_groups + (!!remaining_groups); x++) {
        int base_in = x*3;
        int base_out = x*4;
        out[0] = input[base_in] >> 2;
        out[1] = ((input[base_in] & 0x3) << 4) | (input[base_in + 1] >> 4);
        out[2] = ((input[base_in + 1] << 2) & 0x3C) | (input[base_in + 2] >> 6);
        out[3] = input[base_in + 2] & 0x3F;

        output[base_out] = B64_LOOKUP[out[0]];
        output[1 + base_out] = B64_LOOKUP[out[1]];
        output[2 + base_out] = B64_LOOKUP[out[2]];
        output[3 + base_out] = B64_LOOKUP[out[3]];
    }

    if (remaining_groups > 1) {
        output[4*whole_groups + 4] = '=';
    }
    if (remaining_groups > 0) {
        output[4*whole_groups + 3] = '=';
    }

    return 0;
}

void encode_hex(
        uint8_t *in,
        size_t in_len,
        unsigned char* out)
{
    for (size_t off = 0; off < in_len; off++) {
        snprintf(out+(2*off), 3, "%.2x", *(in+off));
    }
    out[2*in_len - 1] = '\0';
}

void decode_hex(
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

int hex_to_b64(
        char *hex,
        char *b64)
{
    uint8_t in[3];
    int ret;
    int ic=0,oc=0;
    /* read hex 8 "bytes" at a time and convert to uint32 */
    while (0 < (ret = sscanf(hex, "%2hhx%2hhx%2hhx",  &in[0], &in[1], &in[2]))) {
        ic++;
        b64_enc(in, ret, b64);
        hex += 2*ret;
        b64 += ret + 1;
    }
    *b64 = '\0';

    return 0;
}
