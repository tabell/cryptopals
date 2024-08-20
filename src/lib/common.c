#include <ctype.h>
#include "common.h"
#include "list.h"
#include "score.h"
#include "hamming.h"

#define MIN(a,b) ((a) > (b) ? (b) : (a))

int xor(uint8_t *a,   size_t a_len,
        uint8_t *key, size_t key_len,
        uint8_t *out, size_t out_len)
{
    size_t len = MIN(a_len, out_len);
    for (int i = 0; i < len; i++) {
        out[i] = a[i] ^ key[i % key_len];
    }

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

void build_charmap(
        float *charmap){
    for (int i = 0; i < 32; i++) {
        charmap[i] = -10;
    }
    charmap[' '] = 13; /* Estimate */
    charmap['a'] = 8.167;  charmap['A'] = 8.167;
    charmap['b'] = 1.492;  charmap['B'] = 1.492;
    charmap['c'] = 2.782;  charmap['C'] = 2.782;
    charmap['d'] = 4.253;  charmap['D'] = 4.253;
    charmap['e'] = 12.702; charmap['E'] = 12.702;
    charmap['f'] = 2.228;  charmap['F'] = 2.228;
    charmap['g'] = 2.015;  charmap['G'] = 2.015;
    charmap['h'] = 6.094;  charmap['H'] = 6.094;
    charmap['i'] = 6.966;  charmap['I'] = 6.966;
    charmap['j'] = 0.153;  charmap['J'] = 0.153;
    charmap['k'] = 0.772;  charmap['K'] = 0.772;
    charmap['l'] = 4.025;  charmap['L'] = 4.025;
    charmap['m'] = 2.406;  charmap['M'] = 2.406;
    charmap['n'] = 6.749;  charmap['N'] = 6.749;
    charmap['o'] = 7.507;  charmap['O'] = 7.507;
    charmap['p'] = 1.929;  charmap['P'] = 1.929;
    charmap['q'] = 0.095;  charmap['Q'] = 0.095;
    charmap['r'] = 5.987;  charmap['R'] = 5.987;
    charmap['s'] = 6.327;  charmap['S'] = 6.327;
    charmap['t'] = 9.056;  charmap['T'] = 9.056;
    charmap['u'] = 2.758;  charmap['U'] = 2.758;
    charmap['v'] = 0.978;  charmap['V'] = 0.978;
    charmap['w'] = 2.360;  charmap['W'] = 2.360;
    charmap['x'] = 0.150;  charmap['X'] = 0.150;
    charmap['y'] = 1.974;  charmap['Y'] = 1.974;
    charmap['z'] = 0.074;  charmap['Z'] = 0.074;
}

// single letter xor key search
int key_search(
        uint8_t *ct,
        size_t len,
        list_node_t **results)
{
    uint8_t pt[len]; /* plaintext, raw bytes */
    float charmap[256] = { 0 };
    build_charmap(charmap);

    for (uint8_t key=0; key < 255; key++) {
        /* use key to decode to plaintext */
        (void) xor(ct, len, &key, 1, pt, len);

        /* score pt to see if it's readable english */
        float s = score_sentence(charmap, pt, len);
        //dbg("key 0x%x (%c) => score %.2f", key, isprint(key) ? key : ' ', s);

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

int comp_ham(list_node_t *a, list_node_t *b) {
    return (((kl*)a)->ham_norm - ((kl*)b)->ham_norm) < 0 ? 1 : -1;
}

int find_keysize(
        uint8_t *in,
        size_t len)
{
    kl *list = NULL;
    size_t lower=2, upper=60;
    for (size_t keysize = lower; keysize <= upper; keysize++)
    {
        float ham = 0;
        size_t blocks = len / keysize;
        for (int i = 0; i < blocks; i++) {
            ham += hamming(in + (keysize*i), in + (keysize*(i+1)), keysize);
        }
        ham /= (float)blocks;
        float ham_norm = (float)ham / (float)keysize;
        kl *item = calloc(1, sizeof (kl));
        if (!item) break;
        item->ham_norm = ham_norm;
        item->keylen = keysize;
        list_insert_sorted((list_node_t**)&list, (list_node_t*)item, comp_ham);
    }
    log("keysize = %lu bytes, smallest normalized hamming distance = %.2f",
            list->keylen, list->ham_norm);
    int ret = list->keylen;

    /* Clean up memory */
    kl *item = NULL;
    while (NULL != (item = (kl*)list_remove_head((list_node_t**)&list))) {
        free(item);
        item = NULL;
    }

    return ret;
}

