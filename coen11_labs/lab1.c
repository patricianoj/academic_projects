/*
 Patricia Ornelas
 COEN 11 Lab 1
 September 18, 2017
*/

#include <stdio.h>
#include <stdlib.h>

int divide(int, int);

int main(void)
{
	srand((int) time(NULL));
	int score = 0; 
	int divisor = 0, quotient = 0;
	
	// Repeat function 10 times
    for (int i = 0; i < 10; i++)
    {
		divisor = rand() % 12 + 1;
		quotient = rand() % 13;
	        score += divide(divisor, quotient);
	}
	// Print score
  	printf("You got %d correct out of 10\n", score);
  	return 0;
}

int divide(int divisor, int quotient)
{
	int dividend = quotient * divisor;

	// Ask user to guess 
 	printf("What is %d divided by %d?\n", dividend, divisor);
  	int guess;
  	scanf("%d", &guess);
  	
	// Check if user input is correct
	if(guess == quotient)
  	{
    		printf("That's right!\n");
    		return 1;
  	}
  	else	
  	{
    		printf("Incorrect. The correct answer is %d \n", quotient);
    		return 0;
  	}
}

