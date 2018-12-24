#include "lib/common.h"
#include "lib/file.h"
#include "lib/hamming.h"
#include "lib/score.h"

#define INFILE "data/6/ex6.raw.data"

typedef struct key_list_t {
    list_node_t list;
    float ham_norm;
    size_t keylen;
} kl;

int comp_ham(list_node_t *a, list_node_t *b) {
    return (((kl*)a)->ham_norm - ((kl*)b)->ham_norm) < 0 ? 1 : -1;
}

int find_keysize(
        uint8_t *in,
        size_t len)
{
    kl *list = NULL;
    size_t lower=2, upper=60;
    for (size_t keysize = lower; keysize <= upper; keysize++)
    {
        float ham = 0;
        size_t blocks = len / keysize;
        for (int i = 0; i < blocks; i++) {
            ham += hamming(in + (keysize*i), in + (keysize*(i+1)), keysize);
        }
        ham /= (float)blocks;
        float ham_norm = (float)ham / (float)keysize;
        kl *item = calloc(1, sizeof (kl));
        if (!item) break;
        item->ham_norm = ham_norm;
        item->keylen = keysize;
        list_insert_sorted((list_node_t**)&list, (list_node_t*)item, comp_ham);
    }
    log("keysize = %lu bytes, smallest normalized hamming distance = %.2f",
            list->keylen, list->ham_norm);
    int ret = list->keylen;

    /* Clean up memory */
    kl *item = NULL;
    while (NULL != (item = (kl*)list_remove_head((list_node_t**)&list))) {
        free(item);
        item = NULL;
    }

    return ret;
}

int main(void)
{
    uint8_t *buf = NULL;
    int ret;
    size_t bytes;
    if (0 != (ret = file_read_alloc(INFILE, &buf, &bytes))) {
        log("error %d: %s", ret, strerror(-ret));
        return 0;
    }

    size_t keysize = find_keysize(buf, bytes);
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

