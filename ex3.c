#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "common.h"
#include "list.h"

#define log(fmt, ...) printf("%s:%d: " fmt "\n",  __func__, __LINE__, __VA_ARGS__);

typedef struct scored_string {
    list_node_t node; /* must be first member for casting */
    char *ptr;
    int key;
    float score;
} scored_str_t;

int score_compare(
        list_node_t *a,
        list_node_t *b)
{
    float s1 = ((scored_str_t*)a)->score;
    float s2 = ((scored_str_t*)b)->score;
    return (s1 > s2) ? 1 : -1;
}

int ex3(void)
{
    char ct_h[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"; /* cyphertext, hex */
    size_t msglen = sizeof(ct_h) / 2;
    uint8_t ct_r[msglen]; /* cyphertext, raw bytes */
    uint8_t pt_r[msglen]; /* plaintext, raw bytes */

    scored_str_t *head = NULL;

    for (uint8_t key=0; key < 255; key++) {
        hex_to_bytes(ct_h, ct_r);

        char keystr[msglen];
        memset(keystr, key, sizeof(keystr));
        xor(ct_r, keystr, pt_r, msglen);

        float s = score(pt_r, msglen);
        scored_str_t *node = calloc(1, sizeof(scored_str_t));
        node->ptr = strdup(pt_r);
        node->score = s;
        node->key = key;
        list_insert_sorted((list_node_t**)&head, (list_node_t*)node, score_compare);
    }

    scored_str_t *iter = (scored_str_t*)&head;
    if (NULL != (iter = (scored_str_t*)list_next((list_node_t*)iter))) {
        printf("%d: tested against key %c: score=%.2f\n", iter->key, isprint(iter->key) ? iter->key : ' ', iter->score);
            printf("raw: %s\n\n", iter->ptr);
    }

    return 0;
}

