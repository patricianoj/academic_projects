/* Patricia Ornelas 
	COEN 11L
	October 16, 2017
	Monday Lab
    Lab 5
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 21

// Global variables for arrays and size of array
int counter;

struct reservation 
{
	char name[MAX];
	int number;
	struct reservation *next;    
};

struct reservation *head = NULL;
struct reservation *tail = NULL;

// Array of structs
struct reservation waitlist;

// Prototypes for functions
void show_list();
int insert();
void remove_reservation();


int main(void) {
	int validity = 0;
    
	// Lists options for user
	// Loop checks for valid user input
    while(validity != 1) {
		printf("If you want to be added to the waitlist, press '1'. If you want to delete an entry, press '2'. If you want to show the waitlist, press '3'. If you want to quit, press '4'\n");
		int choice;
		int check;

		// Takes input from user to determine function
		scanf("%d", &choice);
		switch(choice){
			case 1:
				// adds name and number of people to bottom of list
				check = insert();

				// While-loop checks if the name is a duplicate
				while(check == 0)
				{
					printf("That name is taken. Try again.\n");
					check = insert();
				}
                
				break;
			
			case 2:
				// deletes an entry
				show_list();
				remove_reservation();
				break;
			
            case 3:
                // shows the list
                show_list();
                break;
                
			case 4:
				// quit
				validity = 1;
				break;
                
            default:
                validity = 0;
		}
	}
	
	return 0;
}

void show_list()
{
	struct reservation *ptr = head;

     // If the list is empty, print message
    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
        while(ptr != NULL)
        {
            printf("Name: %s, Size: %d\n", ptr->name, ptr->number);
            ptr = ptr->next;                
        }
    }
}

int insert()
{
	// ask for name
	char name_entered[MAX];
	printf("Enter Name: (in 20 characters or less) \n");
	scanf("%s", name_entered);
	
	struct reservation *ptr = head;
	struct reservation *ptr2 = tail;
	struct reservation *newr = (struct reservation*)malloc(sizeof(struct reservation));
	
	// Sanity check
	if(newr == NULL)
    {
        printf("Unable to allocate memory.\n");
        return 1;
    }
    else
    {
        // check if name is already taken
        int taken;
        while(ptr != NULL)
		{
			taken = strcmp(name_entered, ptr->name);
			if(taken == 0)
			{
				// if name is taken, returns 0 to exit function
				return 0; 
			}
            ptr = ptr->next;
		}
        
		// ask for number of people
		int people;
		printf("Enter number of people:\n");
		scanf("%d", &people);
	
		// add name and number
		strcpy(newr->name, name_entered);
		newr->number = people;
		newr->next = NULL;
		
        // check if it's the first node to be inserted
        if((head == NULL) && (tail == NULL))
        {
            head = newr;
            tail = newr;
            return 1;
        }
        
		// Insert new node at end & update tail
        tail->next = newr;
        tail = newr;
        
		return 1;
    }
}

void remove_reservation()
{
    // if list is empty, exit function
    if(head == NULL)
        return;
    int search;
	// ask user who to remove
	printf("What table size do you want to remove?\n");
	scanf("%d", &search);

	struct reservation *p = head;
	struct reservation *q = head;
    
	while(p != NULL)
	{
		// Check if current node contains number
		if(p->number <= search)
        {
            // if it's the only node
            if(head == tail)
            {
                head = NULL;
                tail = NULL;
                return;
            }
            break;
        }
		q = p;
		p = p->next;
	}
	// if it isn't found or if the list is empty, return NULL
	if(p == NULL) {
		printf("No tables of that size found!\n");
		return;
	}
	// if it is in the first node
	if(p == head)
    {
		head = head->next;
        free(p);
    }
    else if(p == tail)
    {
        q->next = p->next;
        tail = q;
        free(p);
    }
    else
	{
        q->next = p->next;
        free(p);
	}
}