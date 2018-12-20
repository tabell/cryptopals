#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "common.h"
#include "list.h"
#include "score.h"


int ex3(void)
{
    char ct_h[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"; /* cyphertext, hex */

    /* two ascii characters required per byte */
    size_t len = (sizeof(ct_h) - 1) / 2;

    uint8_t ct[len]; /* cyphertext, raw bytes */
    uint8_t pt[len+1]; /* plaintext, raw bytes */
    pt[len] = '\0';

    /* convert ascii hex to bytes */
    decode_hex(ct_h, ct);

    list_node_t *results = NULL;
    key_search(ct, len, &results);

    score_t *winner = NULL;
    if (NULL != (winner = (score_t*)results)) {
        decode_repeating_xor(winner->ct, pt, len, winner->key);
        printf("%s\nDecoded using (%d) %c\n", pt, winner->key, isprint(winner->key) ? winner->key : ' ');
    }


    return 0;
}

