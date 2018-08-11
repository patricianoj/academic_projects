/* Patricia Ornelas
 COEN 12L
 March 12, 2018
 Monday Lab
 Lab 6 table.c Generic
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define REMOVED 2


struct set {
    int count;
    int length;
    char **elts;
    char *flags;
    int (*compare)();
    unsigned(*hash)();
};


// worse case O(n)
// partitions an array and returns the pivot point
static int partition(SET *sp, void **array, int low, int high) {
    assert(sp != NULL);
    void *pivot = array[high];
    int i = low - 1;
    void *temp;
    for(int j = low; j < high; j++) {
        if((*sp->compare)(array[j], pivot) <= 0) {
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;
    
    return (i+1);
}

// worse case O(n^2)
// sorts an array recursively by partitioning
void quickSort(SET *sp, void **array, int low, int high) {
    assert(sp != NULL);
    if(low < high) {
        int pivot = partition(sp, array, low, high);
        quickSort(sp, array, low, pivot - 1);
        quickSort(sp, array, pivot + 1, high);
    }
}

// worse case runtime O(n)
// searches through hash table to find value or available spot, returns appropriate value for available spot
static int search(SET *sp, void *elt, bool *found) {
    int i, key, firstempty;
    bool foundempty = false;
	for(i = 0; i < sp->length; i++) {
        key = (((*sp->hash)(elt)) + i) % sp->length;
        if(sp->flags[key] == EMPTY) {
            *found = false;
            if(foundempty == false) {
                firstempty = key;
                foundempty = true;
            }
            break;
        }
        else if(sp->flags[key] == FILLED) {
             if((*sp->compare)(sp->elts[key], elt) == 0) {
                *found = true;
                return key;
            }
        }
        else {
            if(foundempty == false) {
                firstempty = key;
                foundempty = true;
            }
        }
    }
    *found = false;
    return firstempty;
}

// Runtime O(n)
// creates and returns set, initializes variables
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->elts = malloc(sizeof (void *) *maxElts);
    assert(sp->elts != NULL);
    sp->flags = malloc(sizeof (int) *maxElts);
    assert(sp->flags != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->compare = compare;
    sp->hash = hash;
    int i;
    for(i = 0; i < maxElts; i++)
        sp->flags[i] = EMPTY;
    return sp;
}

// Runtime O(1)
// frees all variables in set
void destroySet(SET *sp) {
    assert(sp != NULL);
    free(sp->flags);
    free(sp->elts);
    free(sp);
}

// Runtime O(1)
// returns the number of items in hash table
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

// Runtime O(n)
// adds element by checking if it is already in the set
void addElement(SET *sp, void *elt) {
    assert(sp != NULL);
    bool found;
    int position = search(sp, elt, &found);
    if(found == false) {
        assert(sp->count < sp->length);
        sp->elts[position] = elt;
        sp->count = sp->count + 1;
        sp->flags[position] = FILLED;
    }
}

// Runtime O(n)
// removes an item from set if found
void removeElement(SET *sp, void *elt) {
    assert(sp != NULL);
    bool found;
    int position = search(sp, elt, &found);
    if(found == true) {
        sp->flags[position] = REMOVED;
        sp->count--;
    }
}

// Runtime O(n)
// searches and returns an element
void *findElement(SET *sp, void *elt) {
    assert(sp != NULL);
    bool found;
    int position = search(sp, elt, &found);
    if(found != false)
        return sp->elts[position];
    return NULL;
}

// worse case O(n^2)
// returns all elements in list sorted
void *getElements(SET *sp) {
    assert(sp != NULL);
    void **sortedray = malloc(sizeof(void *) * sp->count);
    assert(sortedray != NULL);
    int i, j;
    for(i = 0, j = 0; i < sp->length; i++) {
        if(sp->flags[i] == FILLED)
            sortedray[j++] = sp->elts[i];
    }
    quickSort(sp, sortedray, 0, sp->count-1);
    return sortedray;
}

