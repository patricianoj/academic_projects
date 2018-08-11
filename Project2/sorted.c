/* Patricia Ornelas
 COEN 12L
 January 16, 2018
 Monday Lab
 Lab 2
 sorted.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct set {
    // # of elements in array
    int count;
    // total # of allocated elements
    int length;
    // allocated elements themselves
    char **elts;
};

static int search(SET *sp, char *find, bool *found) {
    assert(sp != NULL);
    int low = 0;
    int mid;
    int high = (sp->count - 1);
    // printf("high: %d mid: %d low: %d\n", high, mid, low);
    while(low <= high) {
        //printf("high: %d mid: %d low: %d\n", high, low, mid);
        mid = (low + high)/2;
        if(strcmp(find, sp->elts[mid]) < 0)
            high = mid -1;
        else if(strcmp(find, sp->elts[mid]) > 0)
            low = mid + 1;
        else {
            *found = true;
            return mid;
        }
    }
    *found = false;
    return low;
    
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
    int i;
    for(i = 0; i < sp->count; i++)
        free(sp->elts[i]);
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
    bool found;
    int position = search(sp, elt, &found);
    if(found == false) {
        assert(sp->count < sp->length);
        elt = strdup(elt);
        int k;
        for(k = sp->count - 1; k > position - 1; k--) {
            sp->elts[k+1] = sp->elts[k];
        }
        sp->elts[position] = elt;
        sp->count = sp->count + 1;
    }
}

// remove elt from the set pointed to by sp
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    bool found;
    int position = search(sp, elt, &found);
    if(found == true) {
        free(sp->elts[position]);
        // shift everything back
        int j;
        for(j = position + 1; j < sp->count; j++)
            sp->elts[j-1] = sp->elts[j];
        sp->count--;
    }
}

// if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    bool found;
    int position = search(sp, elt, &found);
    if(found != false)
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