#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q) {
        list_ele_t *node_free;
        node_free = q->head;
        while (q->head) {
            q->head = q->head->next;
            free(node_free->value);
            free(node_free);
            node_free = q->head;
        }
        free(q);
    }
    return;
}
/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL)
        return false;
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s));
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL)
        q->tail = newh;
    (q->size)++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s));
    newh->next = NULL;
    q->head = newh;
    if (q->head == NULL)
        q->head = newh;
    (q->size)++;
    return false;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL)
        return false;
    list_ele_t *node_free;
    node_free = q->head;
    q->head = q->head->next;
    if (q->tail == node_free)
        q->tail = q->tail->next;
    if (sp) {
        size_t l = strlen(node_free->value);
        strncpy(sp, node_free->value, bufsize - 1);
        if (l > (bufsize - 1)) {
            sp[bufsize - 1] = 0;
        }
    }
    free(node_free->value);
    free(node_free);
    (q->size)--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->size < 2) {
        return;
    }
    list_ele_t **node = &(q->head);
    list_ele_t *cursor = NULL;
    q->head = q->tail;
    q->tail = *node;
    while (*node) {
        list_ele_t *next = (*node)->next;
        (*node)->next = cursor;
        cursor = *node;
        *node = next;
    }
    *node = cursor;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->size < 2) {
        return;
    }
    list_ele_t **a = &q->head;
    list_ele_t **b = &q->head;
    queue_t *q2 = q_new();
    q2->size = (q->size) / 2;
    q->size -= q2->size;
    for (int i = 0; i < q->size; i++) {
        b = &(*b)->next;
    }
    q2->head = *b;
    q_sort(q);
    q_sort(q2);
    while (*a != *b && *b != NULL) {
        int cmp = strcmp((*a)->value, (*b)->value);
        if (cmp >= 0) {
            list_ele_t *tmp = (*b)->next;
            (*b)->next = *a;
            *a = *b;
            *b = tmp;
            if (cmp == 0) {
                a = &(*a)->next;
            }
        }
        a = &(*a)->next;
    }
    return;
}
