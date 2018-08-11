/*  Patricia Ornelas
    COEN 11L
	November 27, 2017
	Monday Lab
	main.c
    Lab 10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "list.h"
#include <pthread.h>
#include <unistd.h>

// initialize global variable
extern struct reservation *heads[4] = {NULL, NULL, NULL, NULL};
extern struct reservation *tails[4] = {NULL, NULL, NULL, NULL};
int validity = 0;

int main(int argc, char *argv[]) {
   
    if(argc < 3)
    {
        printf("The name of the file is missing!\n");
        return 1;
    }
    else
        read_file(argv[1]);
    
    pthread_t thr;
    pthread_create(&thr, NULL, autosaver, NULL);

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
	        pthread_mutex_lock(&mutex);
	        // adds name and number of people to bottom of list
                check = check_name();
                
                // While-loop checks if the name is a duplicate
                while(check == 0)
                {
                    printf("That name is taken. Try again.\n");
                    check = check_name();
                }
                pthread_mutex_unlock(&mutex);
		break;
                
            case 2:
	        pthread_mutex_lock(&mutex);
                // deletes an entry
                show_list();
                // Ask user who to remove
                int search;
                printf("What table size do you want to remove?\n");
                scanf("%d", &search);
                remove_reservation(search, NULL);
                pthread_mutex_unlock(&mutex);
		break;
                
            case 3:
                // shows the list
                show_list();
                break;
                
            case 4:
                // changes size of reservation
	        pthread_mutex_lock(&mutex);
	        show_list();
                change_size();
                pthread_mutex_unlock(&mutex);
		break;
                
            case 5:
	        pthread_mutex_lock(&mutex);
                // reverse list
                for(int i = 0; i < 4; i++)
                    heads[i] = reverse(heads[i]);
                pthread_mutex_unlock(&mutex);
		break;
                
            case 6:
	        pthread_mutex_lock(&mutex);
	        // Read binary list
                read_bfile(argv[2]);
                pthread_mutex_unlock(&mutex);
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

