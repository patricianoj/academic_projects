// bst exam
#include <cctype>     // Provides toupper
#include <iostream>   // Provides cout, cin
#include <cstdlib>    // Provides EXIT_SUCCESS, size_t
#include "bag_bst.h"  // Provides the bag<double> class (with Item as a double)

using namespace std;
using namespace coen79_lab9;

// PROTOTYPES for the functions used in this test program.
void print_menu( );
// Postcondition: A menu of choices for this program has been written to cout.

char get_user_command( );
// Postcondition: The user has been prompted to enter a one character command.
// A line of input (with at least one character) has been read, and the first
// character of the input line is returned.

int four();
int three();
int two();
int one(bag<double> );
void all_tests(bag<double> );

int main( int argc, char* argv[])
{
    bag<double> b1;  // Bags that we'll perform tests on
    char choice; // A command character entered by the user
    
    cout << "I have initialized two empty bags of doubles." << endl;
    
    do
    {
        print_menu( );
        choice = get_user_command( );
        switch (choice)
        {
            case '0': all_tests(b1);
                break;
            case '1': one(b1);
                break;
            case '2': two();
                break;
            case '3': three();
                break;
            case '4': four();
                break;
            case 'q':
            case 'Q': cout << "Exit program." << endl;
                break;
            default: cout << choice << " is invalid. Sorry." << endl;
        }
    }
    while ((toupper(choice) != 'Q'));
    
    return EXIT_SUCCESS;
    
}

/* TEST CASES */
int four() {
    int score = 0;
    cout << "START OF TEST 4" << endl;
    cout << "Testing erase and erase_one functions (20 points)." << endl;
    
    cout << "Testing removal from empty bag (should have no effect" << endl;
    bag<double> empty;
    bool t = empty.erase_one(1);
    if(t == false && empty.size() == 0) {
        score += 1;
        cout << "Test passed" << endl;
    }
    else
        cout << "Test failed" << endl;
    
    cout << "Inserting these: 8 6 10 1 7 10 15 3 13 2 5 11 14 4 12" << endl;
    empty.insert(8);
    empty.insert(6);
    empty.insert(10);
    empty.insert(1);
    empty.insert(7);
    empty.insert(10);
    empty.insert(15);
    empty.insert(3);
    empty.insert(13);
    empty.insert(2);
    empty.insert(5);
    empty.insert(11);
    empty.insert(14);
    empty.insert(4);
    empty.insert(12);
    if(empty.size() == 15)
        cout << "Test passed." << endl;
    else
        cout << "Test failed." << endl;
    
    cout << "Removing 0 (which is not in bag, so bag should be unchanged)... ";
    t = empty.erase(0);
    if(empty.size() == 15 && t == false) {
        score += 5;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 6... ";
    int n = empty.erase(6);
    if(empty.size() == 14 && n == 1) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing one 10... ";
    t = empty.erase_one(10);
    if(empty.size() == 13 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 1... ";
    t = empty.erase_one(1);
    if(empty.size() == 12 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 15... ";
    t = empty.erase_one(15);
    if(empty.size() == 11 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 5... ";
    t = empty.erase_one(5);
    if(empty.size() == 10 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 11... ";
    t = empty.erase_one(11);
    if(empty.size() == 9 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 3... ";
    t = empty.erase_one(3);
    if(empty.size() == 8 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing one 13... ";
    t = empty.erase_one(13);
    if(empty.size() == 7 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing one 2... ";
    t = empty.erase_one(2);
    if(empty.size() == 6 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 14... ";
    t = empty.erase_one(14);
    if(empty.size() == 5 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 4... ";
    t = empty.erase_one(4);
    if(empty.size() == 4 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 12... ";
    t = empty.erase_one(12);
    if(empty.size() == 3 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 8... ";
    t = empty.erase_one(8);
    if(empty.size() == 2 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Removing the 7... ";
    t = empty.erase_one(7);
    if(empty.size() == 1 && t == true) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Inserting more 10's... Removing all 10's... " << endl;
    for(int i = 0; i < 10; ++i)
        empty.insert(10);
    n = empty.erase(10);
    if(empty.size() == 4 && n == 1) {
        score += 1;
        cout << "Test passed." << endl;
    }
    else
        cout << "Test failed." << endl;
    
    cout << "Test 4 got " << score << " points out of a possible 20." << endl;
    cout << "END OF TEST 4\n\n";
    return score;
}

int three() {
    int score = 0;
    cout << "START OF TEST 3" << endl;
    cout << "Testing the assignment operator (10 points)." << endl;
    cout << "A.  Testing that assignment operator works okay for empty bag." << endl;
    bag<double> empty, other;
    other = empty;
    if(other.size() == empty.size()) {
        score += 5;
        cout << "Test passed" << endl;
    }
    else
        cout << "Test failed" << endl;
    
    cout << "B.  Testing assignment operator with 4-item bag" << endl;
    other.insert(1);
    other.insert(1);
    other.insert(1);
    other.insert(1);
    empty = other;
    if(empty.size() == other.size() && empty.count(1) == 4) {
        score += 5;
        cout << "Test passed" << endl;
    }
    else
        cout << "Test failed" << endl;
    cout << "Test 3 got " << score << " points out of a possible 10." << endl;
    cout << "END OF TEST 3\n\n";
    return score;
}

int two() {
    int score = 0;
    cout << "START OF TEST 2" << endl;
    cout << "Testing the copy constructor (10 points)." << endl;
    cout << "A.  Testing that copy constructor works okay for empty bag." << endl;
    bag<double> empty;
    bag<double> other(empty);
    if(other.size() == empty.size()) {
        score += 5;
        cout << "Test passed" << endl;
    }
    else
        cout << "Test failed" << endl;
    cout << "B.  Testing copy constructor with 4-item bag" << endl;
    other.insert(1);
    other.insert(1);
    other.insert(1);
    other.insert(1);
    bag<double> another(other);
    if(another.size() == other.size() && another.count(1) == other.count(1)) {
        score += 5;
        cout << "Test passed" << endl;
    }
    else
        cout << "Test failed" << endl;
    cout << "Test 2 got " << score << " points out of a possible 10." << endl;
    cout << "END OF TEST 2\n\n";
    return score;
}

int one(bag<double> b1) {
    int score = 0;
    cout << "START OF TEST 1" << endl;
    cout << "Testing insert and the constant member functions (60 points)." << endl;
    cout << "A.  Testing size and count for an empty bag." << endl;
    if(b1.size() == 0) {
        score += 5;
        cout << "Test passed" << endl;
    }
    else
        cout << "Test failed" << endl;
    
    cout << "B.  Adding the number 4 to the bag, and then testing size and count." << endl;
    b1.insert(4);
    if(b1.size() == 1) {
        score += 2;
        if(b1.count(4) == 1) {
            score += 3;
            cout << "Test passed" << endl;
        }
    }
    else
        cout << "Test failed" << endl;
    
    cout << "C.  Inserting the number 2 into the bag.Then checking size and count." << endl;
    b1.insert(2);
    if(b1.size() == 2) {
        score += 2;
        if(b1.count(2) == 1) {
            score += 3;
            cout << "Test passed" << endl;
        }
    }
    else
        cout << "Test failed" << endl;
    
    cout << "D.  Inserting the number 1 into the bag.Then checking size and count." << endl;
    b1.insert(1);
    if(b1.size() == 3) {
        score += 5;
        if(b1.count(1) == 1) {
            score += 5;
            cout << "Test passed" << endl;
        }
    }
    else
        cout << "Test failed" << endl;
    
    cout << "E.  Inserting the number 3 into the bag.Then checking size and count." << endl;
    b1.insert(3);
    if(b1.size() == 4) {
        score += 5;
        if(b1.count(3) == 1) {
            score += 5;
            cout << "Test passed" << endl;
        }
    }
    else
        cout << "Test failed" << endl;
    
    cout << "F.  Inserting another 2 into the bag.Then checking size and count." << endl;
    b1.insert(2);
    if(b1.size() == 5) {
        score += 5;
        if(b1.count(2) == 2) {
            score += 5;
            cout << "Test passed" << endl;
        }
    }
    else
        cout << "Test failed" << endl;
    
    cout << "G.  Inserting the numbers 5, 6, and 7 into the bag.Then checking size and count." << endl;
    b1.insert(5);
    b1.insert(6);
    b1.insert(7);
    if(b1.size() == 8) {
        score += 2;
        if(b1.count(5) == 1) {
            score += 1;
            if(b1.count(6) == 1) {
                score += 1;
                if(b1.count(7) == 1) {
                    score += 1;
                    cout << "Test passed" << endl;
                }
            }
        }
    }
    else
        cout << "Test failed" << endl;
    
    cout << "H. Inserting 3000 random items between 0 and 49and then checking size and count." << endl;
    for(int i = 0; i < 3000; ++i) {
        b1.insert(rand() % 49);
    }
    if(b1.size() == 3008) {
        score += 10;
        cout << "Test passed" << endl;
    }
    else
        cout << "Test failed" << endl;
    cout << "Test 1 got " << score << " points out of a possible 60." << endl;
    cout << "END OF TEST 1\n\n";
    return score;
}

void print_menu( )
// Library facilties used: iostream.h
{
    cout << "The following choices are available with 2 bags: " << endl;
    cout << " 0  All tests" << endl;
    cout << " 1  Test insert & const member functions" << endl;
    cout << " 2  Test copy constructor" << endl;
    cout << " 3  Test Assignment operator" << endl;
    cout << " 4  Test erase and erase_one" << endl;
    cout << " Q  Quit the program" << endl;
}

char get_user_command( )
// Library facilties used: iostream.h
{
    char command;
    
    cout << "Enter choice: ";
    cin >> command;
    
    return command;
}

void all_tests(bag<double> b1) {
    int score = 0;
    score += one(b1);
    score += two();
    score += three();
    score += four();
    cout << "Total score: " << score << " out of 100" << endl;
}


