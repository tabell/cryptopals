#include "lib/common.h"
#include "lib/file.h"

int main(
        int argc,
        char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <infile>\n", argv[0]);
        return 0;
    }

    uint8_t *buf = NULL;
    size_t buf_len;
    int ret;

    if (0 != (ret = file_read_alloc(argv[1], &buf, &buf_len))) {
        fprintf(stderr, "error %d loading %s: %s\n", ret, argv[1], strerror(-ret));
    } else {
        char *ct_h = strtok(buf, "\n");
        /* two ascii characters required per byte */
        size_t len = strlen(ct_h) / 2; /* Assume this doesn't change */

        uint8_t ct[len]; /* cyphertext, raw bytes */
        uint8_t pt[len+1]; /* plaintext, raw bytes */
        pt[len] = '\0';

        list_node_t *results = NULL;
        while (ct_h != NULL) {
            /* convert ascii hex to bytes */
            decode_hex(ct_h, ct);
            size_t keysize = find_keysize(ct, len, 16, 16);
            fprintf(stderr,"keysize=%lu: %s\n", keysize, ct_h);
            ct_h = strtok(NULL, "\n");
        }
    }

    free(buf);
    return 0;
}
