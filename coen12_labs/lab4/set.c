/* Patricia Ornelas
 * COEN 12L M 5:15pm
 * Lab 4 set.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include "set.h"
#include "list.h"

#define NODE struct node
#define LIST struct list
#define SET struct set

struct set {
    int count;
    int length;
    void **elts;
    int (*compare)();
    unsigned(*hash)();
};

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

// Runtime O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->elts = malloc(sizeof (void *) *maxElts);
    assert(sp->elts != NULL);
    sp->count = 0;
    sp->length = maxElts/20;
    sp->compare = compare;
    sp->hash = hash;
    int i;
    for(i = 0; i < sp->length; i++)
        sp->elts[i] = createList(sp->compare);
    return sp;
}

// Runtime O(n)
void destroySet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->length; i++)
        destroyList(sp->elts[i]);
    free(sp->elts);
    free(sp);
}

int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

// Runtime O(n)
// adds element if unique to set
void addElement(SET *sp, void *elt) {
    assert(sp != NULL);
    int key = ((*sp->hash)(elt)) % sp->length;
    void *data = findItem(sp->elts[key], elt);
    if(data == NULL) {
        addFirst(sp->elts[key], elt);
        sp->count++;
    }
}

// Runtime O(n)
void removeElement(SET *sp, void *elt) {
    assert(sp != NULL);
    int key = ((*sp->hash)(elt)) % sp->length;
    void *data = findItem(sp->elts[key], elt);
    if(data != NULL) {
        removeItem(sp->elts[key], elt);
        sp->count--;
    }
}

// Runtime O(n^2)
void *findElement(SET *sp, void *elt) {
    assert(sp != NULL);
    void *data;
    for(int i = 0; i < sp->length; i++) {
        data = findItem(sp->elts[i], elt);
        if(data != NULL)
            break;
    }
    return data;
}

// Runtime O(n^3)
void *getElements(SET *sp) {
    assert(sp != NULL);
    void **tempray, **listitems;
    int i, j, k = 0;
    tempray = (void *)malloc(sizeof(void *) * sp->count);
    assert(tempray != NULL);
    for(i = 0; i < sp->length; i++) {
        listitems = (void *)malloc(sizeof(void *) * numItems(sp->elts[i]));
        listitems = getItems(sp->elts[i]);
        for(j = 0; j < numItems(sp->elts[i]); j++) {
            tempray[k] = listitems[j];
            k++;
        }
    }
    return tempray;
}