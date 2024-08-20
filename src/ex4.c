#include "lib/file.h"
#include "lib/common.h"
#include "lib/list.h"
#include "lib/score.h"

#define DATA_PATH "data/4/in"


int main(void)
{
    unsigned char *buf = NULL;
    int ret;
    size_t bytes;
    if (0 != (ret = file_read_alloc(DATA_PATH, &buf, &bytes))) {
        return ret;
    }

    char *ct_h = strtok(buf, "\n");
    /* two ascii characters required per byte */
    size_t len = strlen(ct_h) / 2; /* Assume this doesn't change */

    uint8_t ct[len]; /* cyphertext, raw bytes */
    uint8_t pt[len+1]; /* plaintext, raw bytes */
    pt[len] = '\0';

    list_node_t *results = NULL;
    while (ct_h != NULL) {
        fprintf(stderr,".");
        /* convert ascii hex to bytes */
        decode_hex(ct_h, ct);

        key_search(ct, len, &results); /* Append results */
        ct_h = strtok(NULL, "\n"); /* Not thread safe */
    }
    printf("\n");

    score_t *winner = NULL;
    if (NULL != (winner = (score_t*)results)) {
        xor(winner->ct, sizeof(winner->ct), &winner->key, 1,  pt, len);

        char cth[len*2];
        encode_hex(winner->ct, len, cth);
        printf("Decoded %s using (%c) 0x%x\n%s\n",
                cth, isprint(winner->key) ? winner->key : ' ', winner->key, pt);
    }


    return 0;
}

