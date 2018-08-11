/* Patricia Ornelas 
	COEN 11L
	September 25, 2017
	Lab 2 
*/
#include <stdio.h>
#include <string.h>

// Global variables for arrays and size of array
int counter;
int num_array[20];
char names_array[20][21];

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
	for(int i = 0; i < counter; i++) {
            printf("Name: %s. People: %d\n", names_array[i], num_array[i]);
	}
}

int insert()
{
	// check if array is full 
	if(counter == 20)
		return 2;

	// ask for name
	char name_entered[21];
	printf("Enter Name: (in 20 characters or less) \n");
	scanf("%s", name_entered);
	
	int taken;	

	// check if name is already taken
	for(int i= 0; i < counter; i++)
	{
		taken = strcmp(name_entered, names_array[i]);
		if(taken == 0)
		{
			// returns 0 to exit function
			return 0; 
		}
		// copies user input into names array
		strcpy(names_array[counter], name_entered);
        
    }
        
	// ask for number of people
    int people;
    printf("Enter number of people:\n");
     
	scanf("%d", &people);
	
	// add name and number
	strcpy(names_array[counter], name_entered);
	num_array[counter] = people;
	counter++;
    return 1;
}

void remove_reservation()
{
    int search;
	// ask user who to remove
	printf("What table size do you want to remove?\n");
	scanf("%d", &search);

    int found;
	for(int i = 0; i < counter; i++)
	{
		if(num_array[i] == search)
		{
			// the name is found
			// shift all other elements to the left
			for(int j = i; j < counter; j++)
			{
				strcpy(names_array[j], names_array[j+1]);
				num_array[j] = num_array[j+1];
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
