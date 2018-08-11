/*  Patricia Ornelas
    COEN 11L
	November 13, 2017
	Monday Lab
	files.c
    Lab 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "list.h"

void clear_list()
{
    struct reservation *p;
    for(int i = 3; i >= 0; i--)
    {
        p = heads[i];
        while(p != NULL)
        {
            remove_reservation(0, p->name);
            p = p->next;
        }
    }
}

char * header()
{
    char * headerstr = "Name\t\tGroup Size\n-----------------------------------\n";
    return headerstr;
}

void read_file(char *filename)
{
    char name[MAX];
    int number;
    // open file
    FILE *fp = fopen(filename, "r");
    // sanity check
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    // offset to skip header
    fseek(fp, strlen(header()), SEEK_SET);
    // loop through lines of file
    while(fscanf(fp, "%s %d", name, &number) == 2)
        insert(number, name);
    // close file
    fclose(fp);
}

void write_file(char *filename)
{
    struct reservation *p;
    // open file
    FILE *fp = fopen(filename, "w");
    // sanity check
    if(fp == NULL)
        printf("Error opening file\n");
    // print header
    fprintf(fp, "%s", header());
    for(int i = 0; i < 4; i++)
    {
        p = heads[i];
        // loop through linked list
        while(p != NULL)
        {
            fprintf(fp, "%s\t\t%d\n", p->name, p->number);
            p = p->next;
        }
    }
    // close file
    fclose(fp);
}

void read_bfile(char *filename)
{
    clear_list();
    struct reservation p;
    // open file
    FILE *fp = fopen(filename, "rb");
    // sanity check
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    for(int i = 0; i < 4; i ++)
    {
        // loop through lines of file
        while(fread(&p, sizeof(struct reservation), 1, fp) > 0)
            insert(p.number, p.name);
    }
    // close file
    fclose(fp);
}

void write_bfile(char *filename)
{
    struct reservation *p;
    // open file
    FILE *fp = fopen(filename, "wb");
    // sanity check
    if(fp == NULL)
        printf("Error opening file\n");
    for(int i = 0; i < 4; i++)
    {
        p = heads[i];
        // loop through linked list
        while(p != NULL)
        {
            fwrite(p, sizeof(struct reservation), 1, fp);
            p = p->next;
        }
    }
    // close file
    fclose(fp);
}

