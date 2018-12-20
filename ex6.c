#include "common.h"
#include "file.h"
#include "hamming.h"

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
    size_t lower=2, upper=40;
    for (size_t keysize = lower; keysize <= upper; keysize++)
    {
        uint8_t *block[] = { in, in + keysize };
        int ham = hamming(block[0], block[1], keysize);
        float ham_norm = (float)ham / (float)keysize;
        kl *item = calloc(1, sizeof (kl));
        if (!item) break;
        item->ham_norm = ham_norm;
        item->keylen = keysize;
        list_insert_sorted((list_node_t**)&list, (list_node_t*)item, comp_ham);
    }
    log("keysize = %lu bytes, normalized hamming distance = %.2f",
            list->keylen, list->ham_norm);
    int ret = list->keylen;

    /* Clean up memory */
    list_node_t *item = NULL;
    while (NULL != (item = list_remove_head((list_node_t**)&list))) {
        free(item);
        item = NULL;
    }

    return ret;
}


#define INFILE "ex6.raw.data"
int ex6(void)
{
    uint8_t *buf = NULL;
    int ret;
    size_t bytes;
    if (0 != (ret = file_read_alloc(INFILE, &buf, &bytes))) {
        log("error %d: %s", ret, strerror(-ret));
        return 0;
    }

    size_t keysize = find_keysize(buf, bytes);

    size_t block_count = bytes / keysize;
    uint8_t *blocks[keysize];
    for (int i = 0; i < keysize; i++) {
        blocks[i] = malloc(bytes);
    }

    for (int i = 0; i < keysize; i++) {
        memcpy(
        blocks[i] + (i*keysize),
        buf + (i*keysize),
        keysize);
    }


    for (int i = 0; i < keysize; i++) {
        free(blocks[i]);
    }

    free(buf);
    return 0;

}

