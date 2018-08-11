/* Patricia Ornelas
 * COEN 12L M 5:15pm
 * Lab 5 pqueue.c
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "pqueue.h"
#include "pack.h"
#define NODE struct node


// O(1)
// function to create node
static NODE *mkNode(int count, NODE *left, NODE *right) {
	NODE *root = malloc(sizeof(NODE));
	assert(root != NULL);
	root->count = count;
	root->parent = NULL;
	// connect children to parent
	if(left != NULL)
		left->parent = root;
	if(right != NULL)
		right->parent = root;
	return root;
}

// O(1)
// function to compare two leaves
static int nodecmp(NODE *node1, NODE *node2) {
    return (node1->count < node2->count) ? -1: (node1->count > node2->count);
}

// recursive function that returns the depth of a given node
static int depth(NODE *child) {
    // recursive until parent node = null then return 0 else return 1+parent depth
    if(child->parent == NULL)
        return 0;
    else
        return 1 + depth(child->parent);
}

int main(int argc, char *argv[]) {
	// step 1: read through file and count frequency of each character
	// initialize arrays
    int counts[257];
    for(int k = 0; k < 257; k++)
        counts[k] = 0;
    
    NODE *leaves[257];
    for(int n = 0; n < 257; n++)
        leaves[n] = NULL;
    
	int c;
    assert(argc == 3);
	
    // loop through file to determine frequency for each character
    FILE *fp = fopen(argv[1], "rb");
	assert(fp != NULL);
	while((c = getc(fp)) != EOF) {
        counts[c]++;
	}
	fclose(fp);
    
    PQ *pq = createQueue(*nodecmp);
	// step 2: create a leaf node for each char
    int i;
    for(i = 0; i < 257; i++) {
        if(counts[i] > 0) {
            leaves[i] = mkNode(counts[i], NULL, NULL);
            addEntry(pq, leaves[i]);
        }
    }
    
    // add node at end
    NODE *other = malloc(sizeof(NODE));
    other->count = 0;
    other->parent = NULL;
    leaves[256] = other;
    addEntry(pq, leaves[256]);
    
    // step 3: build huffman tree from priority queue
	while(numEntries(pq) > 1) {
		NODE *r = removeEntry(pq);
		NODE *l = removeEntry(pq);
		NODE *p = mkNode(l->count + r->count, l, r);
		addEntry(pq, p);
	}
    
    // step 4: print encoding
    int nodedepth, totalbits;
    for(i = 0; i < 257; i++) {
        if(leaves[i] != NULL) {
            nodedepth = depth(leaves[i]);
            totalbits = nodedepth * leaves[i]->count;
            printf(isprint(i)? "'%c'" : "'%03o'", i);
            printf(" %d x %d bits = %d bits\n", counts[i], nodedepth, totalbits);
        }
    }
    
    pack(argv[1], argv[2], leaves);
	return 0;
}
