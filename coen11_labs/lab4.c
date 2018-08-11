/* Patricia Ornelas 
	COEN 11L
	October 9, 2017
	Monday Lab
    Lab 3
*/

#include <stdio.h>
#include <string.h>
#define MAX 3

// Global variables for arrays and size of array
int counter = 0;

typedef union
{
	// members
	char school_name[MAX];
	float salary;
	int year;
	
} PERSON_INFO;

struct person 
{
	char name[MAX];
	int age;
	PERSON_INFO uni;
};

// Array of structs
struct person people[MAX];

// Prototypes for functions
void show_list();
int insert();
void remove_person();

int main(void) {
	int validity = 0;
    
	// Lists options for user
	// Loop checks for valid user input
    while(validity != 1) {
		printf("Insert '0'. Delete '1'. Show list '2'. Quit '3'\n");
		int choice;
		int check;

		// Takes input from user to determine function
		scanf("%d", &choice);
		switch(choice){
			case 0:
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
			
			case 1:
				// deletes an entry
				show_list();
				remove_person();
				break;
			
            case 2:
                // shows the list
                show_list();
                break;
                
			case 3:
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
	struct person *ptr = people;
	
	// traverse array of structs
	for(int i = 0; i < counter; i++, ptr++){
		// print information depending on age
		if(ptr->age <= 21)
			printf("Name: %s. Age: %d. School name: %s\n", ptr->name, ptr->age, ptr->uni.school_name);
		if((ptr->age > 21) && (ptr->age < 65))
			printf("Name: %s. Age: %d. Monthly salary: %f\n", ptr->name, ptr->age, ptr->uni.salary);
		if(ptr->age >= 65)
			printf("Name: %s. Age: %d. Retirement Year: %d\n", ptr->name, ptr->age, ptr->uni.year);
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

    struct person *ptr = people;
    
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
        
	// ask for age
    int number;
    printf("Enter age:\n");
	scanf("%d", &number);
	
    char school[MAX];
    float m_salary;
    int r_year;
    
	// add name and number
	strcpy(people[counter].name, name_entered);
	people[counter].age = number;
	if(number <= 21){
		printf("Enter school name:\n");
		scanf("%s", school);
		strcpy(people[counter].uni.school_name, school);
	}
	else if((number > 21) && (number < 65)){
		printf("Enter monthly salary:\n");
		scanf("%f", &m_salary);
		people[counter].uni.salary = m_salary;
	}
	else if(number >= 65){
		printf("Enter year of retirement:\n");
		scanf("%d", &r_year);
		people[counter].uni.year = r_year;
	}
	
	counter++;
    return 1;
}

void remove_person()
{
    char search[MAX];
	// ask user who to remove
	printf("Who do you want to remove?\n");
	scanf("%s", search);

	struct person *ptr = people;

    int found;
    for(int i = 0; i < counter; i++, ptr++){
        found = strcmp(search, ptr->name);
        if(found == 0)
        {
			// the name is found
			// copy last
            people[i] = people[counter-1];
            
			// Decrement array size by 1;
            printf("%s deleted!\n", search);
			counter--;
            break;
		}
	}
    if(found != 0)
        printf("Person not found!\n");
    
}

