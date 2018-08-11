/*  Patricia Ornelas
    COEN 11L
	November 13, 2017
	Monday Lab
	list.h
    Lab 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

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

// Prototypes for functions
void show_list();
int insert(int, char *);
int check_name();
void remove_reservation(int, char *);
void change_size();
struct reservation * reverse(struct reservation *);
int find_list(char *);
