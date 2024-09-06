#include "lib/file.h"
#include "lib/common.h"
#include "lib/list.h"
#include "lib/score.h"

#define DATA_PATH "../data/4/in"


int main(void)
{
    char *buf = NULL;
    int ret;
    size_t bytes;
    if (0 != (ret = file_read_alloc(DATA_PATH, &buf, &bytes))) {
        return ret;
    }

    char *ct_h = strtok(buf, "\n");
    /* two ascii characters required per byte */
    size_t enc_len = strlen(ct_h) + 1;
    size_t raw_len = enc_len / 2; /* Assume this doesn't change */
    size_t chunks = bytes/enc_len;
    fprintf(stderr, "read %lu bytes, first line %lu, expecting %lu chunks\n", bytes, enc_len, chunks);

    uint8_t ct[raw_len]; /* cyphertext, raw bytes */
    uint8_t pt[raw_len]; /* plaintext, raw bytes */

    list_node_t *results = NULL;
    while (ct_h != NULL) {
        fprintf(stderr,".");
        /* convert ascii hex to bytes */
        decode_hex(ct_h, ct);

        key_search(ct, raw_len, &results); /* Append results */
        ct_h = strtok(NULL, "\n"); /* Not thread safe */
    }
    printf("\n");

    score_t *winner = NULL;
    if (NULL != (winner = (score_t*)results)) {
        xor(winner->ct, sizeof(winner->ct), &winner->key, 1,  pt, raw_len);
        printf("%s\n", pt);

        char winner_enc[enc_len];
        encode_hex(winner->ct, raw_len, winner_enc);
        printf("Decoded %s using (%c) 0x%x\n%s\n",
                winner_enc, isprint(winner->key) ? winner->key : ' ', winner->key, pt);
    }


    return 0;
}

