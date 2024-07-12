#include <unistd.h>
#include <string.h>

#include "lib/common.h"
#include "lib/file.h"

void ice_str(
        char *in,
        size_t len,
        char *out_h)
{
    char out[len];
    repeating_xor(in, out, len, "ICE", 3);
    encode_hex(out, len, out_h);
}

int main(
        void)
{
    char str1[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

    size_t len = sizeof(str1) - 1;
    char out1[len * 2];

    ice_str(str1, len, out1);
    printf("%s\n", out1);


    return 0;
}


