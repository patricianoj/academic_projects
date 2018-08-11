/*  Patricia Ornelas
    COEN 11L
	November 27, 2017
	Monday Lab
	list.h
    Lab 10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#define MAX 21
int validity;

// Global variables for arrays and size of array
struct reservation
{
    char name[MAX];
    int number;
    struct reservation *next;
};

// Array of structs
struct reservation *heads[4];
struct reservation *tails[4];
pthread_mutex_t mutex;

// Prototypes for functions
void show_list();
int insert(int, char *);
int check_name();
void remove_reservation(int, char *);
void change_size();
struct reservation * reverse(struct reservation *);
int find_list(char *);
void *autosaver();
