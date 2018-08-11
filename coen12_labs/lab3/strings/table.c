/* Patricia Ornelas
 COEN 12L
 February 11, 2018
 Monday Lab
 Lab 3 table.c Strings
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
};

unsigned strhash(char *s) {
    unsigned hash = 0;
    while (*s != '\0')
        hash = 31 * hash + *s ++;
    return hash;
}

// worse case runtime O(n)
static int search(SET *sp, char *elt, bool *found) {
    int i, key, firstempty;
    bool foundempty = false;
    for(i = 0; i < sp->length; i++) {
        key = (strhash(elt) + i) % sp->length;
        if(sp->flags[key] == EMPTY) {
            *found = false;
            if(foundempty == false) {
                firstempty = key;
                foundempty = true;
            }
            break;
        }
        else if(sp->flags[key] == FILLED) {
            if(strcmp(sp->elts[key], elt) == 0) {
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
SET *createSet(int maxElts) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->elts = malloc(sizeof (char *) *maxElts);
    assert(sp->elts != NULL);
    sp->flags = malloc(sizeof (int) *maxElts);
    assert(sp->flags != NULL);
    sp->count = 0;
    sp->length = maxElts;
    int i;
    for(i = 0; i < maxElts; i++) {
        sp->flags[i] = EMPTY;
    }
    return sp;
}

// Runtime O(1)
void destroySet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->count; i++) {
        if(sp->flags[i] == FILLED)
            free(sp->elts[i]);
    }
    
    free(sp->flags);
    free(sp->elts);
    free(sp);
}

// Runtime O(1)
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

// Runtime O(n)
void addElement(SET *sp, char *elt) {
    assert(sp != NULL);
    // ensure elt is unique
    bool found;
    int position = search(sp, elt, &found);
    if(found == false) {
        assert(sp->count < sp->length);
        elt = strdup(elt);
        sp->elts[position] = elt;
        sp->count = sp->count + 1;
        sp->flags[position] = FILLED;
    }
}

// Runtime O(n)
void removeElement(SET *sp, char *elt) {
    assert(sp != NULL);
    bool found;
    int position = search(sp, elt, &found);
    if(found == true) {
        free(sp->elts[position]);
        sp->flags[position] = REMOVED;
        sp->count--;
    }
}

// Runtime O(n)
char *findElement(SET *sp, char *elt) {
    assert(sp != NULL);
    bool found;
    int position = search(sp, elt, &found);
    if(found != false)
        return sp->elts[position];
    return NULL;
}

// Runtime O(n)
char **getElements(SET *sp) {
    assert(sp != NULL);
    int i, j;
    char **tempray;
    tempray=(char **) malloc(sizeof (char *) *sp->count);
    for(i = 0, j = 0; i <sp->length; i++) {
        if(sp->flags[i] == FILLED)
            tempray[j++] = sp->elts[i];
    }
    return tempray;
}
