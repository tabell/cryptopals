#include "lib/common.h"
#include "lib/file.h"
#include "lib/hamming.h"
#include "lib/score.h"

#define INFILE "data/6/ex6.raw.data"

int main(void)
{
    uint8_t *buf = NULL;
    int ret;
    size_t bytes;
    if (0 != (ret = file_read_alloc(INFILE, &buf, &bytes))) {
        log("error %d: %s", ret, strerror(-ret));
        return 0;
    }

    size_t keysize = find_keysize(buf, bytes, 2, 60);
    dbg("trying keysize %ld", keysize);
    size_t block_count = bytes / keysize;
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
    char out[bytes];
    repeating_xor(buf, out, bytes, key, keysize);
    fprintf(stdout,"%s\n", out);
    free(buf);
    return 0;

}

