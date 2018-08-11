// data structure: sorted (by age) doubly-linked non-circular list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>

#define NODE struct node
#define LIST struct list

struct node {
	int id;
	int age;
	NODE *prev;
	NODE *next;
};

struct list {
	int count;
	NODE *head;
};


// allocates memory and initializes variables for list
LIST *createList() {
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
        lp->head->prev = lp->head;
	return lp;
}

// destroys everything in linked list starting from the last node
void destroyList(LIST *lp) {
    assert(lp != NULL);
    if(lp->count > 0) {
        NODE *current = lp->head->next;
        NODE *del = lp->head;
        // loop to delete every node in list
        while(current != lp->head) {
            del = current;
            current = del->next;
            free(del);
        }
    }
    free(lp);
}

// inserts node into linked list
void insertStudent(LIST *lp, int newid, int newage) {
    assert(lp != NULL);
    NODE *new = malloc(sizeof(NODE));
    new->id = newid;
    new->age = newage;
    NODE *current = lp->head->next;
    // loop through list until place is found to put student
    while(current != lp->head) {
        if(current->age >= newage) {
	    new->next = current;
	    new->prev = current->prev;
	    current->prev->next = new;
	    current->prev = new;
	    lp->count++;
	    return;
        }
        current = current->next;
    }
    new->next = lp->head;
    new->prev = lp->head->prev;
    lp->head->prev->next = new;
    lp->head->prev = new;
    lp->count++;
}

// searches by id
// returns corresponding node or NULL if not found
NODE *searchID(LIST *lp, int searchid) {
    assert(lp != NULL);
    NODE *current = lp->head->next;
    // loop through linked list to find id
    while(current != lp->head) {
        if(searchid == current->id) {
            printf("ID %d found. ", searchid);
	    return current;
	}
        current = current->next;
    }
    printf("ID %d not found\n", searchid);
    return NULL;
}

// searches by age
// returns corresponding node or NULL if not found
NODE *searchAge(LIST *lp, int searchage) {
    assert(lp != NULL);
    NODE *current = lp->head->next;
    // loop through linked list to find age
    while(current != lp->head) {
        if(searchage == current->age) {
            printf("first person with age %d has ID %d\n", searchage, current->id);
	    return current;
	}
        current = current->next;
    }
    printf("Age not found\n");
    return NULL;
}

// finds node with corresponding ID, deletes that node
void removeStudent(LIST *lp, int delID) {
    assert(lp != NULL);
    NODE *del;
    del = searchID(lp, delID);
    del->next->prev = del->prev;
    del->prev->next = del->next;
    free(del);
    printf("Removed student with ID %d successfully\n", delID); 
}

// returns the largest age gap among students
int maxAgeGap(LIST *lp) {
    assert(lp != NULL);
    int min = lp->head->next->age;
    int max = lp->head->prev->age;
    int ageGap = max - min;
    return ageGap;
}

// prints all IDs and their corresponding ages
void printData(LIST *lp) {
    assert(lp != NULL);
    NODE *current = lp->head->next;
    printf("entering loop\n");
    while(current != lp->head) {
        printf("ID: %d. Age: %d\n", current->id, current->age);
        current = current->next;
    }
}
