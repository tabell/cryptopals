#include <stdlib.h>

int b64_enc(
	unsigned char *input,
    size_t in_len,
	unsigned char *output);

void encode_hex(
        uint8_t *in,
        size_t in_len,
        unsigned char* out);

void decode_hex(
        unsigned char *in,
        uint8_t *out);

int hex_to_b64(
        const unsigned char *hex,
        unsigned char *b64);
