/*  Patricia Ornelas
    COEN 11L
	November 13, 2017
	Monday Lab
	main.c
    Lab 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "list.h"

// initialize global variable
extern struct reservation *heads[4] = {NULL, NULL, NULL, NULL};
extern struct reservation *tails[4] = {NULL, NULL, NULL, NULL};


int main(int argc, char *argv[]) {
   
    if(argc < 3)
    {
        printf("The name of the file is missing!\n");
        return 1;
    }
    else
        read_file(argv[1]);
    
    int validity = 0;
    
    // Lists options for user
    // Loop checks for valid user input
    while(validity != 1)
    {
        printf("Insert '1'. Delete '2'. Show '3'. Change size '4'. Reverse '5'. Read binary file '6'. Quit '7'. \n");
        int choice;
        int check;
        
        // Takes input from user to determine function
        scanf("%d", &choice);
        switch(choice){
            case 1:
                // adds name and number of people to bottom of list
                check = check_name();
                
                // While-loop checks if the name is a duplicate
                while(check == 0)
                {
                    printf("That name is taken. Try again.\n");
                    check = check_name();
                }
                break;
                
            case 2:
                // deletes an entry
                show_list();
                // Ask user who to remove
                int search;
                printf("What table size do you want to remove?\n");
                scanf("%d", &search);
                remove_reservation(search, NULL);
                break;
                
            case 3:
                // shows the list
                show_list();
                break;
                
            case 4:
                // changes size of reservation
                show_list();
                change_size();
                break;
                
            case 5:
                // reverse list
                for(int i = 0; i < 4; i++)
                    heads[i] = reverse(heads[i]);
                break;
                
            case 6:
                // Read binary list
                read_bfile(argv[2]);
                break;
                
            case 7:
                // quit
                write_file(argv[1]);
                write_bfile(argv[2]);
                validity = 1;
                break;
                
            default:
                validity = 0;
        }
    }
    
    return 0;
}

