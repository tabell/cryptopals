#include <stdio.h>
#include <stdlib.h>
#include "../list.h"

struct li {
    list_node_t list;
    int num;
};

int comp(list_node_t *a, list_node_t *b)
{
    int an = ((struct li*)a)->num;
    int bn = ((struct li*)b)->num;
    int ret =  an - bn;
    return ret;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("usage: %s <numbers separated by spaces>\n", argv[0]);
        return 0;
    }

    struct li *head = NULL;

    for (int i = 1; i < argc; i++) {
        struct li *item = calloc(1, sizeof(struct li));
        item->num = atoi(argv[i]);
        printf("inserting %d\n", item->num);
        if (!head) {
            head = item;
        } else {
            list_insert_sorted((list_node_t**)&head, (list_node_t*)item, comp);
        }
    }

    printf("\nwalking list:\n");

    list_node_t *iter = (list_node_t*)head;
    do {
        printf("%d\n", ((struct li*)iter)->num);
    } while (NULL != (iter = list_next(iter)));

    return 0;
}


