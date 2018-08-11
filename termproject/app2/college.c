#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "set.h"

#define maxelts 3001
#define SET struct set

int main() {
    SET *students = createDataSet(maxelts);
    srand(time(NULL));
    int randid = ( rand() % 2 ) + 1;
    int randage = ( rand() % 13 ) + 18;
    insertStudent(students, randid, randage);

    // populate set with students of random ages and IDs    
    int i;
    for(i = 1; i < 1000; i++) {
	randage = ( rand() % 13 ) + 18;
	randid = randid + ( rand() % 2 ) + 1;
        insertStudent(students, randid, randage);
    }

    // generate random ID to search and remove 
    int searchid = ( rand() % 2000 ) + 1;
    printf("Searching for ID %d\n", searchid);
    removeStudent(students, searchid);
 
    destroyDataSet(students);
    return 0;
}
