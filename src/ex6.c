#include "lib/common.h"
#include "lib/file.h"
#include "lib/hamming.h"
#include "lib/score.h"

#define INFILE "data/6/ex6.raw.data"

// Challenge 6, break repeating key XOR

int main(void)
{
    uint8_t *buf = NULL;
    int ret;
    size_t buflen = 0;
    if (0 != (ret = file_read_alloc(INFILE, &buf, &buflen))) {
        log("error %d: %s", ret, strerror(-ret));
        return 0;
    }

    size_t keysize = find_keysize(buf, buflen);
    dbg("trying keysize %ld", keysize);
    size_t block_count = buflen / keysize;
    uint8_t *block = NULL;
    char key[keysize + 1];
    key[keysize] = '\0';
    for (int i = 0; i < keysize; i++) {
        block = malloc(block_count);

        for (int j = 0; j < block_count; j++) {
            memcpy( block + j, buf + i + (j*keysize), 1);
        }
        
        list_node_t *results = NULL;
        key_search(block, block_count, &results); /* Append results */
        key[i] = ((score_t*)results)->key;
        list_node_t *item = NULL;
        while (NULL != (item = list_remove_head((list_node_t**)&results))) {
            free(item);
            item = NULL;
        }

        free(block);
    }

    log("key is %s", key);
    char out[buflen];
    xor(buf, buflen,  key, keysize, out, buflen);
    fprintf(stdout,"%s\n", out);
    free(buf);
    return 0;

}

