#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define REMOVED 2
#define SET struct set

// initializes variables & returns pointer to a set
SET *createDataSet(int maxelts) {
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxelts;
	sp->ageray = malloc(sizeof(int)*maxelts);
	assert(sp->ageray!= NULL);
	sp->idray = malloc(sizeof(int)*maxelts);
	assert(sp->idray != NULL);	
	sp->flags = malloc(sizeof(int)*maxelts);
	assert(sp->flags != NULL);
	int i;
	for(i = 0; i < maxelts; i++)
		sp->flags[i] = EMPTY;
	return sp;
}

// frees all elements in set
void destroyDataSet(SET *sp) {
	assert(sp != NULL);
	free(sp->ageray);
	free(sp->idray);
	free(sp->flags);
	free(sp);
}

// returns ID if location of ID if found or the first empty spot if not
int searchID(SET *sp, int searchid, bool *found) {
	int i, key, firstempty;
	bool foundempty = false;
	// loop through hash table to find appropriate spot for new entry
        for(i = 0; i < sp->length; i++) {
		key = ((searchid) + i )% sp->length;
		if(sp->flags[key] == EMPTY) {
			*found = false;
			if(foundempty == false) {
				firstempty = key;
				foundempty = true;
			}
			break;
		}
		else if(sp->flags[key] == FILLED) {
			if(sp->idray[key] == searchid) {
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

// given an age and ID, adds entry to set
void insertStudent(SET *sp, int newid, int newage) {
	assert(sp != NULL);
	bool found;
	int position = searchID(sp, newid, &found);
	if(found == false) {
		assert(sp->count < sp->length);
		sp->idray[position] = newid;
		sp->ageray[position] = newage;
		sp->count = sp->count + 1;
		sp->flags[position] = FILLED;
	}
}

// deletes student given an ID to search
void removeStudent(SET *sp, int idsearch) {
	assert(sp != NULL);
	bool found;
	int position = searchID(sp, idsearch, &found);
	if(found == true) {
		printf("ID %d found. ", idsearch);
		sp->flags[position] = REMOVED;
		sp->count--;
		printf("ID %d removed\n", idsearch);
	}
	else
		printf("ID %d not found\n", idsearch);
}
