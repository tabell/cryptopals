#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#include "list.h"

#define log(fmt, ...) fprintf(stderr, fmt "\n", __VA_ARGS__);
#define dbg(fmt, ...) fprintf(stderr, "%s:%d: " fmt "\n",  __func__, __LINE__, __VA_ARGS__);

typedef struct key_list_t {
    list_node_t list;
    float ham_norm;
    size_t keylen;
} kl;

void encode_hex(
        uint8_t *in,
        size_t in_len,
        unsigned char* out);

void decode_hex(
        unsigned char *in,
        uint8_t *out);

int xor(uint8_t *a, size_t a_len,
        uint8_t *key, size_t key_len,
        uint8_t *out, size_t out_len);

int key_search(
        uint8_t *ct,
        size_t len,
        list_node_t **results);

int find_keysize(
        uint8_t *in,
        size_t len);
