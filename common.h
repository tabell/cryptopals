#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#include "list.h"

#define log(fmt, ...) printf("%s:%d: " fmt "\n",  __func__, __LINE__, __VA_ARGS__);

void encode_hex(
        uint8_t *in,
        size_t in_len,
        unsigned char* out);

void decode_hex(
        unsigned char *in,
        uint8_t *out);

void xor(
        uint8_t *a,
        uint8_t *b,
        uint8_t *out,
        size_t len);

int single_xor(
        uint8_t *in,
        uint8_t *out,
        size_t len,
        char key);

int key_search(
        uint8_t *ct,
        size_t len,
        list_node_t **results);

int repeating_xor(
        uint8_t *in,
        uint8_t *out,
        size_t msg_len,
        char *key,
        size_t key_len);
