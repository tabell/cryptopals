#include "lib/common.h"
#include "lib/base64.h"

int hex_to_b64(
        char *hex,
        char *b64)
{
    uint8_t in[3];
    int ret;
    int ic=0,oc=0;
    /* read hex 8 "bytes" at a time and convert to uint32 */
    while (0 < (ret = sscanf(hex, "%2hhx%2hhx%2hhx",  &in[0], &in[1], &in[2]))) {
        ic++;
        b64_enc(in, ret, b64);
        hex += 2*ret;
        b64 += ret + 1;
    }
    *b64 = '\0';

    return 0;
}

int main(void) {
    char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char correct_out[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    char output[512];
    int ret = hex_to_b64(input, output);
    printf("ret: %d\ninput: %s\noutput: %s\n",
            ret, input, output);
	if (0 != strncmp(output, correct_out, strlen(correct_out))) {
		printf("Something went wrong\n");
	}
    return 0;
}

