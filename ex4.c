#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#include "common.h"
#include "list.h"
#include "score.h"

#define DATA_PATH "ex4.data"

int ex4(void)
{
    int fd = -1;
    if (0 > (fd = open("ex4.data", 0))) {
        log("error %d opening %s: %s", errno, DATA_PATH, strerror(errno));
        return -errno;
    }

    struct stat statbuf = {0};
    if (0 != fstat(fd, &statbuf)) {
        log("error %d stating %s: %s", errno, DATA_PATH, strerror(errno));
        return -errno;
    }

    char *buf = malloc(statbuf.st_size);
    if (!buf) {
        errno = ENOMEM;
        log("error %d allocating %lu bytes: %s", errno, statbuf.st_size, strerror(errno));
        return -errno;
    }

    int ret;
    if (statbuf.st_size > (ret = read(fd, buf, statbuf.st_size))) {
        if (ret > 0) {
            log("only read %d bytes", ret);
            return -EIO;
        } else {
            log("error %d reading from %s: %s", errno, DATA_PATH, strerror(errno));
            return -errno;
        }
    }

    char *ct_h = strtok(buf, "\n");
    /* two ascii characters required per byte */
    size_t len = strlen(ct_h) / 2;

    uint8_t ct[len]; /* cyphertext, raw bytes */
    uint8_t pt[len+1]; /* plaintext, raw bytes */
    pt[len] = '\0';

    list_node_t *results = NULL;
    while (ct_h != NULL) {
        log("trying to decode: %s", ct_h);

        /* convert ascii hex to bytes */
        decode_hex(ct_h, ct);

        key_search(ct, len, &results); /* Append results */
        ct_h = strtok(NULL, "\n"); /* Not thread safe */
    }

    score_t *winner = NULL;
    if (NULL != (winner = (score_t*)results)) {
        decode_repeating_xor(winner->ct, pt, len, winner->key);
        printf("%s\nDecoded from %s using (%d) %c\n",
                pt, winner->ct, winner->key, isprint(winner->key) ? winner->key : ' ');
    }


    return 0;
}

