#include <stddef.h>
#include "list.h"

typedef int (*list_compare_fn_t)(list_node_t *a, list_node_t *b);

void list_insert_sorted(
        list_node_t **head,
        list_node_t *new,
        list_compare_fn_t compare)
{
    list_node_t *p1 = *head;
    list_node_t *h = *head;
    list_node_t *p0 = NULL;

    while (1) {
        if (!p1 || compare(new, p1) > 0) {
            new->next = p1;
            if (p0) {
                p0->next = new;
            } else {
                *head = new;
            }
            break;
        } else {
            if (p1->next) {
                p0 = p1;
                p1 = p1->next;
            } else {
                p1->next = new;
                break;
            }
        }
    }
}

void list_append(
        list_node_t *list,
        list_node_t *new)
{
    list_node_t *tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = new;
}

list_node_t *list_next(
        list_node_t * list)
{
    return list->next;
}

