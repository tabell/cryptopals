#include <unistd.h>
#include <string.h>

#include "common.h"
#include "file.h"

void ice_str(
        char *in,
        size_t len,
        char *out_h)
{
    char out[len];
    repeating_xor(in, out, len, "ICE", 3);
    encode_hex(out, len, out_h);
}
int ice_file(
        char *filename)
{
    unsigned char *buf;
    int ret = file_read_alloc(filename, &buf);
    if (!ret) {
        return ret;
    }
    size_t len = strlen(buf);
    char out[len + 1];

    ice_str(buf, len+1, out);

    printf("%s\n", out);

    free(buf);
    return 0;
}

int ex5(
        void)
{
    char str1[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

    size_t len = sizeof(str1) - 1;
    char out1[len * 2];

    ice_str(str1, len, out1);
    printf("%s\n", out1);


    return 0;
}


