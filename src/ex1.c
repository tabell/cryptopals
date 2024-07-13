#include "lib/common.h"
#include "lib/encoding.h"


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

