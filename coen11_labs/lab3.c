/* Patricia Ornelas 
	COEN 11L
	October 2, 2017
	Monday Lab
    Lab 3
*/

#include <stdio.h>
#include <string.h>
#define MAX 21

// Global variables for arrays and size of array
int counter;

struct reservation 
{
	char name[MAX];
	int number;
};

// Array of structs
struct reservation waitlist[MAX];

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
				if(check == 2)
					printf("Sorry, the list is full.\n");
                
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
	struct reservation *ptr = waitlist;
    
	for(int i = 0; i < counter; i++, ptr++){
		printf("Name: %s. People: %d\n", ptr->name, ptr->number);
	}
}

int insert()
{
	// check if array is full 
	if(counter == MAX)
		return 2;

	// ask for name
	char name_entered[MAX];
	printf("Enter Name: (in 20 characters or less) \n");
	scanf("%s", name_entered);
	
	struct reservation *ptr = waitlist;

	// check if name is already taken
	int taken;	
	for(int i = 0; i < counter; i++, ptr++){
		// taken = strcmp(name_entered, names_array[i]);
		taken = strcmp(name_entered, ptr->name);
		if(taken == 0)
		{
			// returns 0 to exit function
			return 0; 
		}
    }
        
	// ask for number of people
    int people;
    printf("Enter number of people:\n");
     
	scanf("%d", &people);
	
	// add name and number
	strcpy(ptr->name, name_entered);
	ptr->number = people;
	counter++;
    return 1;
}

void remove_reservation()
{
    int search;
	// ask user who to remove
	printf("What table size do you want to remove?\n");
	scanf("%d", &search);

	struct reservation *ptr = waitlist;
	struct reservation *ptr2 = waitlist;
    struct reservation *ptr3 = waitlist;

    int found;
    for(int i = 0; i < counter; i++, ptr++){
		if(ptr->number == search)
		{
			// the name is found
			// shift all other elements to the left
            ptr2 = ptr;
            for(int j = i; j < counter; j++, ptr2++){
                ptr3 = ptr2 + 1;
				strcpy(ptr2->name, ptr3->name);
				ptr2->number = ptr3->number;
			}
            found = 0;
			// Decrement array size by 1;
            printf("%d deleted!\n", search);
			counter--;
            break;
		}
	}
    if(found != 0)
        printf("No tables of that size found!\n");
    
}