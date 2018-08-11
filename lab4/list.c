/* Patricia Ornelas
 COEN 12L
 February 25, 2018
 Monday Lab
 Lab 4 list.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include "list.h"

#define NODE struct node
#define LIST struct list

struct node {
    void *data;
    NODE *prev;
    NODE *next;
};

struct list {
    int count;
    NODE *head;
    int (*compare)();
};

// Runtime O(1)
// allocates memory and initializes variables for list
LIST *createList(int (*compare)()) {
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

// Runtime O(n)
// destroys everything in linked list starting from the last node
void destroyList(LIST *lp) {
    assert(lp != NULL);
    if(lp->count > 0) {
        NODE *current = lp->head->next;
        NODE *del = lp->head;
        while(current != lp->head) {
            del = current;
            current = del->next;
            free(del);
        }
    }
    free(lp);
}

// Runtime O(1)
// returns number of items in list
int numItems(LIST *lp) {
    assert(lp != NULL);
    return lp->count;
}

// Runtime O(1)
void addFirst(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;
    new->next = lp->head->next;
    new->prev = lp->head;
    lp->head->next->prev = new;
    lp->head->next = new;
    lp->count++;
}

// Runtime O(1)
void addLast(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->data = item;
    new->next = lp->head;
    new->prev = lp->head->prev;
    lp->head->prev->next = new;
    lp->head->prev = new;
    lp->count++;
}

// Runtime O(1)
void *removeFirst(LIST *lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE *temp = lp->head->next;
    temp->next->prev = lp->head;
    lp->head->next = temp->next;
    void *p = temp->data;
    lp->count--;
    free(temp);
    return p;
}

// Runtime O(1)
void *removeLast(LIST *lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE *temp = lp->head->prev;
    lp->head->prev = temp->prev;
    void *p = temp->data;
    lp->count--;
    free(temp);
    return p;
}

// Runtime O(1)
void *getFirst(LIST *lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    return lp->head->next->data;
}

// Runtime O(1)
void *getLast(LIST *lp) {
    assert(lp != NULL);
    assert(lp->count > 0);
    return lp->head->prev->data;
}

// Runtime O(n)
void removeItem(LIST *lp, void *item) {
    assert(lp != NULL);
    assert(lp->count > 0);
    NODE *current = lp->head->next;
    while(current != lp->head) {
        if((*lp->compare)(current->data, item) == 0) {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            lp->count--;
            free(current);
            break;
        }
        current = current->next;
    }
}

// Runtime O(n)
void *findItem(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE *current = lp->head->next;
    while(current != lp->head) {
        if((*lp->compare)(current->data, item) == 0)
            return current->data;
        current = current->next;
    }
    return NULL;
}

// Runtime O(n)
void *getItems(LIST *lp) {
    assert(lp != NULL);
    int i = 0;
    void **tempray;
    NODE *temp = lp->head->next;
    tempray = malloc(sizeof(void *) * lp->count);
    assert(tempray != NULL);
    while(i < lp->count && temp != lp->head) {
        tempray[i] = temp->data;
        temp = temp->next;
        i++;
    }
    return tempray;
}