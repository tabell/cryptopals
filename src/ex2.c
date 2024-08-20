#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lib/common.h"


int main(void)
{
    char* str_a = "1c0111001f010100061a024b53535009181c";
    char* str_b = "686974207468652062756c6c277320657965";

    uint8_t a[18] = { 0 };
    uint8_t b[18] = { 0 };
    uint8_t out[18];

    decode_hex(str_a, a);
    decode_hex(str_b, b);

    xor(a, sizeof(a), b, sizeof(b), out, sizeof(out));

    for (int i=0; i < sizeof(out); i++) {
        printf("%c%c xor %c%c = %c\n",
                str_a[2*i], str_a[(2*i)+1],
                str_b[2*i], str_b[(2*i)+1],
                out[i]);
    }

    return 0 == strncmp(out, "the kid don't play", sizeof(out)) ? 0 : -EIO;
}

