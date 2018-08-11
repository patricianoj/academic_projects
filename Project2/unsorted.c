/* Patricia Ornelas
 COEN 12L
 January 16, 2018
 Monday Lab
 Lab 2
 unsorted.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <assert.h>

struct set {
    // # of elements in array
    int count;
    // total # of allocated elements
    int length;
    // allocated elements themselves
    char **elts;
};

static int search(SET *sp, char *find) {
    assert(sp != NULL);
    for(int i = 0; i < sp->count; i++) {
        if(strcmp(sp->elts[i], find) == 0)
            return i;
    }
    return -1;
}

// return a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts) {
    // allocate memory for structure
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    // allocate memory for elts
    sp->elts = malloc(sizeof (char *) *maxElts);
    assert(sp->elts != NULL);
    sp->count = 0;
    sp->length = maxElts;
    return sp;
}

// deallocate memory associated with the set pointed to by sp
void destroySet(SET *sp) {
    assert(sp != NULL);
    for(int i = 0; i < sp->count; i++) {
        free(sp->elts[i]);
    }
    free(sp->elts);
    free(sp);
}

// return the number of elements in the set pointed to by sp
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

// add elt to the set pointed to by sp
void addElement(SET *sp, char *elt) {
    assert(sp != NULL);
    // ensure elt is unique
    int found = search(sp, elt);
    if(found == -1) {
        assert(sp->count < sp->length);
        elt = strdup(elt);
        sp->elts[sp->count++] = elt;
    }
}

// remove elt from the set pointed to by sp
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    int position = search(sp, elt);
    if(position != -1) {
        free(sp->elts[position]);
        sp->elts[position] = sp->elts[sp->count-1];
        sp->count--;
    }
    // shift everything back ... for(int i = position; i < sp->count; i++) {
}

// if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    int position = search(sp, elt);
    if(position != -1)
        return sp->elts[position];
    return NULL;
}

// allocate and return an array of elements in the set pointed to by sp
char **getElements(SET *sp) {
    assert(sp!=NULL);
    char **tempray;
    tempray=(char **) malloc(sizeof (char *) *sp->count);
    return memcpy(tempray, sp->elts, sp->count*sizeof(char *));
}
