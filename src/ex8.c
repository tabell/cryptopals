#include <stdio.h>
#include "common.h"
#include "file.h"

int main(int argc, char** argv) {
    int ret;
    const int keysize = 16;

    if (argc < 2) {
        fprintf(stderr,"usage: %s <list of ciphertexts>\n", argv[0]);
        return 0;
    }

    size_t buflen = 0;
    char *buf = NULL;

    printf("reading file of possible ciphertexts\n");
    if (0 != (ret = file_read_alloc(argv[1], &buf, &buflen))) {
        log("error %d: %s", ret, strerror(-ret));
        return 0;
    }

    int i = 0;

    printf("for each ciphertext: ");
    printf("produce the best plaintext guess, score each guess, choose the higehst score");
    char *line = strtok(buf, "\n");
    if (line == NULL) return 0;

    size_t len = strlen(line);

    while (line != NULL) do {
        log("line %d: %s\n", i++, line);

        // convert hex to bytes
        size_t block_count = buflen / keysize;

        char ct[buflen/2]; // hex string needs two chars per input byte
                                       //
        decode_hex(ct_h, ct);
        // make guess
        // score guess
        // add score to sorted struct

        line = strtok(NULL, "\n");
    }

    // print highest scored struct

    return 0;
}
