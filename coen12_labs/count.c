/* COEN 12L
   January 8, 2018
   Monday Lab
    Lab 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[]) {
    // check that there is a filename
    if(argc == 1) {
        printf("The name of the file is missing!\n");
        return -1;
    }
    // open file
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }
    // count words
    int count = 0;
    char word[MAX_WORD_LENGTH];
    while(fscanf(fp, "%s", word) == 1) {
        count++;
    }
    // close file & output result
    printf("%d total words\n", count);
    fclose(fp);
    return 0;
}