#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define EMPTY 0
#define FILLED 1
#define REMOVED 2
#define SET struct set

struct set {
    int count;
    int length;
    int *idray;
    int *ageray;
    char *flags;
};

SET *createDataSet(int);

void destroyDataSet(SET *);

int searchID(SET *, int, bool *);

void insertStudent(SET *, int, int);

void removeStudent(SET *, int);
