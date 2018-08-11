# Lab 1 - Division Test
Requirements:
* Do 10 times
  * Generate two numbers between 0 and 12 randomly–divisor (cannot be zero) and quotient
  * Output the dividend (divisor * quotient) and the divisor
  * Input the answer
  * Compare the answer with the quotient
  * Output right or wrong
  * If the answer is wrong, output the quotient
  * Count the number of correct answers
  * Show the total score to the user
* Create a function to handle each division
* The main function generates the numbers and passes them as arguments to the division function
* The division function returns 1 if the user is right and 0 if the user is wrong 
* The main function counts the number of right answers in the loop

# Lab 2 - Restaurant Waiting List
The waiting list is created interactively with the following commands
* 1 <name> <number> Adds the name and number of people specified to the bottom of the list
* 2 <size> Removes (show and delete) oldest entry which fits the size of the table
* 3 Shows the list, name and number, from oldest to newest
* 4 Quits
Requirements:
* Global variables: 2 arrays and a counter
* Loop forever accepting commands
* 3 functions: insert, remove, and list
* Do not allow names to repeat
* List mechanism
  * Your list should stay in the oldest-to-newest order
  * Always insert a new entry at the bottom
  * Always shift entries up after deleting one

# Lab 3 - Restaurant Waiting List
Change lab 2 to use an array of structures

# Lab 4 - People List
Commands
* 0 input a person
  * Name, Age, Status
* 1 delete a person
  * Name
* 2 show the current list of info
* 3 quit
Implementation requirements:
* 1 array of structures
* Each struct has three members
  * name - char array
  * age - int
  * status – union (type depends on age)
* Each union has three members
  * school name (age <= 21) char array
  * salary per month (21 < age < 65) float
  * year of retirement (age >= 65) int
 
# Lab 5 - Restaurant Waiting List with Linked List
Using a linked list where each node has a reservation name and the number of people in the group

# Lab 6 - Restaurant Waiting List with Group Size Ranges
Restaurant Waiting List with 4 ranges of group sizes
* 1-2
* 3-4
* 5-6
* Greater than 7
Use an array of linked lists. One list per range

# Lab 7 - Restaurant Waiting List with File Input/Output
Initially, the waiting list may be either empty or formed with information read from a file. At the end, the updated waiting list is saved into a file. The waiting list is created/modified  interactively, except that command quit will save the info into a file. The name of the file is an argument for the program. 

# Lab 8 - Extension of Lab 7
Add the following functionality: 
* Read and write using a binary file
* Reverse the linked lists using recursion

# Lab 9 - Split code from Lab 8

# Lab 10 - Autosave list to file
Have an auto-saver thread in a forever loop to save the info from the list to atext file every 5 seconds.
