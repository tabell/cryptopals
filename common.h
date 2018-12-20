#ifndef CPALS_COMMON_H
#define CPALS_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

void bytes_to_hex(
        uint8_t *in,
        size_t in_len,
        unsigned char* out);

void hex_to_bytes(
        unsigned char *in,
        uint8_t *out);

void xor(
        uint8_t *a,
        uint8_t *b,
        uint8_t *out,
        size_t len);

float score(
        char* text,
        size_t len);
#endif /* CPALS_COMMON_H */
