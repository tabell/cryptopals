#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "lib/common.h"
#include "lib/file.h"

int main(
        void)
{
    char in[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    char correct_out[] = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";


    size_t len = strlen(in); // 75 chars
    assert(len == 74);
    uint8_t out[len];
    
    printf("sizeof(in) = %lu\n", len);

    // XOR
    xor((uint8_t *)in, len,
        (uint8_t *)"ICE", 3,
        (uint8_t *)out, len);

    // Encode result to hex
    char out_hex[(len) * 2 + 1]; // hex string needs two chars per input byte
    encode_hex((uint8_t *)out, len, (char *) out_hex);

    printf("%s\n", out_hex);

    assert(0 == strcmp(out_hex, correct_out));

    return 0;
}


