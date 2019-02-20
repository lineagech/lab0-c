/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    list_ele_t *curr = q->head;
    while (curr != NULL) {
        list_ele_t *tmp = curr->next;
        free(curr->value);
        free(curr);
        curr = tmp;
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL)
        return false;
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL)
        q->tail = newh;

    newh->value = malloc(strlen(s) + 1);
    if (newh->value == NULL)
        return false;
    memcpy(newh->value, s, strlen(s));
    newh->value[strlen(s)] = '\0';

    q->size++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    if (q == NULL)
        return false;

    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    if (q->tail != NULL)
        q->tail->next = newt;
    q->tail = newt;
    if (q->head == NULL)
        q->head = newt;

    newt->next = NULL;
    newt->value = malloc(strlen(s) + 1);
    if (newt->value == NULL)
        return false;
    memcpy(newt->value, s, strlen(s));
    newt->value[strlen(s)] = '\0';

    q->size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    list_ele_t *target;
    if (q == NULL || q->size == 0)
        return false;
    target = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;

    if (sp != NULL) {
        size_t value_str_len = strlen(target->value);
        if (value_str_len >= bufsize) {
            strncpy(sp, target->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        } else {
            strncpy(sp, target->value, value_str_len);
            sp[value_str_len] = '\0';
        }
    }
    free(target->value);
    free(target);
    q->size--;

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;
    else
        return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    list_ele_t *curr = q->head;
    list_ele_t *prev = NULL;

    if (q == NULL)
        return;

    q->tail = curr;
    while (curr != NULL) {
        list_ele_t *tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    q->head = prev;
}
