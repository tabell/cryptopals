#include <ctype.h>
#include "common.h"
#include "list.h"
#include "score.h"

void encode_hex(
        uint8_t *in,
        size_t in_len,
        unsigned char* out)
{
    for (size_t off = 0; off < in_len; off++) {
        snprintf(out+(2*off), 3, "%.2x", *(in+off));
    }
    out[2*in_len - 1] = '\0';
}
void decode_hex(
        unsigned char *in,
        uint8_t *out)
{
    int ret = 0;
    size_t offset = 0;
    while (0 < sscanf(in + offset*2, "%2hhx", out + offset))
    {
        offset++;
    }
}

void xor(
        uint8_t *a,
        uint8_t *b,
        uint8_t *out,
        size_t len)
{
    for (int x = 0; x < len; x++) {
        out[x] = a[x] ^ b[x];
    }
}

int repeating_xor(
        uint8_t *in,
        uint8_t *out,
        size_t msg_len,
        char *key,
        size_t key_len)
{
    char keystr[msg_len];
    for (int i = 0; i < msg_len; i++) {
        keystr[i] = key[i % key_len];
    }

    xor(in, keystr, out, msg_len);
    return 0;
}
int single_xor(
        uint8_t *in,
        uint8_t *out,
        size_t len,
        char key)
{
    /* key is single-char repeating */
    char keystr[len];
    memset(keystr, key, sizeof(keystr));

    xor(in, keystr, out, len);
    return 0;
}

int float_compare(
        list_node_t *a,
        list_node_t *b)
{
    float s1 = ((score_t*)a)->score;
    float s2 = ((score_t*)b)->score;
    return (s1 > s2) ? 1 : -1;
}

int key_search(
        uint8_t *ct,
        size_t len,
        list_node_t **results)
{
    uint8_t pt[len]; /* plaintext, raw bytes */

    for (uint8_t key=0; key < 255; key++) {
        /* use key to decode to plaintext */
        (void) single_xor(ct, pt, len, key);

        /* score pt to see if it's readable english */
        float s = score_sentence(pt, len);

        /* sort scores so we can take highest */
        score_t *node = calloc(1, sizeof(score_t));
        node->score = s;
        node->key = key;
        node->ct = malloc(len);
        memcpy(node->ct, ct, len);
        list_insert_sorted((list_node_t**)results, (list_node_t*)node, float_compare);
    }

    return 0;
}
