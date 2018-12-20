#include <stdio.h>
#include "../file.h"

int main(
        int argc,
        char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        return 0;
    }

    unsigned char *buf = NULL;
    ice_file(argv[1]);
    return 0;
}

