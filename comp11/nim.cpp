/******************
 * Patricia Ornelas
 * Comp 11
 * Homework 3
 * Problem 2
 ******************/

#include <iostream>
#include <stdlib.h>
#include <cstdlib> 
#include <ctime>
using namespace std;

int main()
{
	srand((unsigned)time(0));
	int coin = 0;
	char coin_flip;
	int take = 0;
	int beans = 0;
   	int i_take = ((rand() % 3) + 1);
    char rand_flip;
	int user_points = 0;
	int computer_points = 0;
	bool game_over = false;

	// loop 3 times for 3 rounds of game
	for (int round = 0; round < 3; round++)
	{
		// restart variables at the beginning of each round
		game_over = false;
	 	beans = ((rand() % 30) + 5);
		cout << beans;
	    coin = ((rand() % 2) + 1);
		if (coin == 1) 
		{
			rand_flip = 'H';
		}
		if (coin == 2) 
		{
			rand_flip = 'T';
		}
	    
		cout << "Game " << round + 1 << ". I'll flip a coin. Heads or tails? " <<
         	"Enter captial H or capital T." << endl;
    	cin >> coin_flip;

		// while loop ensures that user inputs 'H' or 'T'
		while ((coin_flip != 'H') && (coin_flip != 'T')) 
		{
			cout << "Enter captial H or capital T. Heads or tails? " << endl;
    		cin >> coin_flip;
		}
	
		// allow player to start if the coin lands on their flip
	    if (rand_flip == coin_flip)
   	 	{
	    	cout << "You start." << endl; 
        	do
	    	{
				cout<< "There are " << beans << " beans. " <<
        			"How many do you take?" << endl;
				cin >> take;
				// ensure that user only puts in an acceptable number
				// of beans based on the rules of the game
				while ((take > beans) || (take > 3) || (take < 0))
				{
					cout << "You can only 1, 2, or 3 beans." << endl;
					cin >> take;
				}
				beans = beans - take;
		  	  	// check if the game is over
				if (beans == 0)
            	{
					game_over = true;
					cout << "You lose this round." << endl;
					computer_points += 1;
				}
	    		else
				{
			 	  	cout << "There are " << beans << " beans left. "
        				"I'll take " << i_take << "." << endl;
					beans = beans - i_take;
					// check if the game is over
					if (beans <= 0)
           	 		{
						game_over = true;
						cout << "You win this round." << endl;
						user_points += 1;
					}
					i_take = ((rand() % 3) + 1);
				}
    		} while (game_over == false);
		}
	
		// have computer start if the coin lands on their flip
    	if (rand_flip != coin_flip)
    	{
    		cout << "I start. There are " << beans << " beans. " <<
        		"I'll take " << i_take << "." << endl;
	    	beans = beans - i_take;
			do
	    	{
				cout<< "There are " << beans << " beans. " <<
        			"How many do you take?" << endl;
				cin >> take;
				// ensure that user only puts in an acceptable number
				// of beans based on the rules of the game
				while ((take > beans) || (take > 3) || (take < 0))
				{
					cout << "You can only 1, 2, or 3 beans." << endl;
					cin >> take;
				}
				beans = beans - take;
		    	if (beans == 0)
            	{
					// check if the game is over
					game_over = true;
					cout << "You lose this round." << endl;
					computer_points += 1;
				}
	    		else
				{
			  	 	cout << "There are " << beans << " beans left. "
        				"I'll take " << i_take << "." << endl;
					beans = beans - i_take;		


					if (beans <= 0)
            		{
						game_over = true;
						cout << "You win this round." << endl;
						user_points += 1;
					}
					i_take = ((rand() % 3) + 1);
				}
    		} while (game_over == false);
		}
	}
	
	// determine and announce winner based on points
	if (computer_points > user_points)
	{
		cout << "I win. Better luck next time" << endl;
	}
	else
    {
		cout << "Congratulations! You win!" << endl;
	}
    return 0;    
}
