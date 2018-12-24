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
        (void) single_xor(ct, pt, len, key);

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
