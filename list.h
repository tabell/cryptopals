#ifndef _ALEX_LIST_H
#define _ALEX_LIST_H
typedef struct list_node list_node_t;

typedef int (*list_compare_fn_t)(list_node_t *a, list_node_t *b);

void list_insert_sorted(
        list_node_t **list,
        list_node_t *new,
        list_compare_fn_t compare);

struct list_node {
    list_node_t *next;
};

void list_append(
        list_node_t *list,
        list_node_t *new);

list_node_t *list_next(
        list_node_t * list);

int float_compare(
        list_node_t *a,
        list_node_t *b);
#endif /* _ALEX_LIST_H */
