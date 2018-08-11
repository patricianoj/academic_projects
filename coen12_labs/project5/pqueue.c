/* Patricia Ornelas
 * COEN 12L M 5:15pm
 * Lab 5 pqueue.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "pqueue.h"

struct pqueue {
    int count;
    int length;
    void **data;
    int (*compare)();
};

// O(1)
// function that returns a pointer to a new priority queue using compare as its comparison function
PQ *createQueue(int (*compare)()) {
    PQ *pq = malloc(sizeof (PQ));
    assert(pq != NULL);
    pq->count = 0;
    pq->length = 10;
    pq->compare = compare;
    pq->data = malloc(sizeof (void *) * 10);
    assert(pq->data != NULL);
    return pq;
}

// O(1)
// function to deallocate memory associated with the priority queue pointed to by pq
void destroyQueue(PQ *pq) {
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}

// O(1)
// function that returns the number of entries in the priority queue pointed to by pq
int numEntries(PQ *pq) {
    assert(pq != NULL);
    return pq->count;
}

// O(n)
// function that adds an entry to the prioirty queue
void addEntry(PQ *pq, void *entry) {
    assert(pq != NULL);
    //printf("entry: %d\n", &entry);
    if(pq->count == pq->length) {
        pq->length *= 2;
        pq->data = realloc(pq->data, sizeof(void *) * pq->length);
        assert(pq->data != NULL);
    }
    pq->data[pq->count] = entry;
    int childindex = pq->count;
    int parentindex = (pq->count - 1) / 2;
    while((*pq->compare)(pq->data[childindex], pq->data[parentindex]) == -1 ) {
        void *temp = pq->data[parentindex];
        pq->data[parentindex] = pq->data[childindex];
        pq->data[childindex] = temp;
        childindex = parentindex;
        parentindex = (parentindex - 1) / 2;
    }
    pq->count++;
}

// O(n)
// function that removes and returns the smallest entry from the priority queue
void *removeEntry(PQ *pq) {
    assert(pq != NULL);
    assert(pq->count > 0);
    void *ogroot = pq->data[0];
    pq->data[0] = pq->data[pq->count-1];
    int minchild, parent = 0;
    pq->count--;
    // set values of parent's left and right children
    int lchild = parent * 2 + 1;
    int rchild = parent * 2 + 2;
    // loop through array until parent is root or it is fully reheaped
    while(parent < pq->count) {
	// case 1: both left and right children exist, compare to find the minimum
	// case 2: only the left child exists, left child is the minimum
	// case 3: only the right child exists, right child is the minimum 
	// case 4: neither child exists, end function
        if(lchild < pq->count && rchild < pq->count) {
            if((*pq->compare)(pq->data[lchild], pq->data[rchild]) == -1) {
                minchild = lchild;
            }
            else {
                minchild = rchild;
            }
        } else if(lchild < pq->count) {
            minchild = lchild;
        } else {
            return ogroot;
        }
        if((*pq->compare)(pq->data[parent], pq->data[minchild]) == 1 ) {
            void *temp = pq->data[minchild];
            pq->data[minchild] = pq->data[parent];
            pq->data[parent] = temp;
            parent = minchild;
            lchild = parent * 2 + 1;
            rchild = parent * 2 + 2;
        } else {
            break;
        }
    }
    return ogroot;
}
