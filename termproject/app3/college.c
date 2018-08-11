#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#define NODE struct node
#define LIST struct list
#define maxelts 3001

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
LIST *createList();

// destroys everything in linked list starting from the last node
void destroyList(LIST *);

// inserts node into linked list
void insertStudent(LIST *, int , int );

// finds node with corresponding ID, deletes that node
void removeStudent(LIST *, int );

// searches by id or age
// returns corresponding node or NULL if not found
NODE *searchID(LIST *, int);
NODE *searchAge(LIST *, int);

// prints all data in list
void printData(LIST *);

// returns the largest age gap among students
int maxAgeGap(LIST *);

int main() {
    LIST *students = createList();
    srand(time(NULL));
    int randid = ( rand() % 2 ) + 1;
    int randage = ( rand() % 13 ) + 18;
    insertStudent(students, randid, randage);

    // populate linked list with students of random ages and IDs
    int i;
    for(i = 1; i < 1000; i++) {
        randage = ( rand() % 13 ) + 18;
        randid = randid + ( rand() % 2 ) + 1;
        insertStudent(students, randid, randage);
    }
    
    // printData(students);	
    
    // generate random ID to search and remove if found
    int searchid = ( rand() % 2000 ) + 1;
    NODE *p = searchID(students, searchid);
    if(p != NULL) 
        removeStudent(students, searchid);
    
    // generate random age to search and print
    int searchage = ( rand() % 13 ) + 18;
    searchAge(students, searchage);
    
    // caluclate and return maximum age gap among students
    int gap = maxAgeGap(students);
    printf("max age gap: %d\n", gap);

    destroyList(students);
    return 0;
}
