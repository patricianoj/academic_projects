//
//  part2.cpp
//  Lab 1
//
//  Created by Patricia Nataly Ornelas on 4/9/18.
//  Copyright © 2018 SCU. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*
    precondition: none
    postcondition: a pattern of all digits alternatingly reversed 
        is printed to the screen with an increasing number of 
        spaces before each line
*/

int main(int argc, const char * argv[]) {
    int spaces = 0;
    string numbers = "0123456789";
    string reverse = "9876543210";
    
    for(int j = 0; j < 5; j++) {
        // print line with spaces and then string
        cout << setw(numbers.length() + spaces) << numbers << '\n';
        // increment the number of spaces before each line
        spaces++;
        cout << setw(reverse.length() + spaces) << reverse << '\n';
        spaces++;
    }
    
    
    cout << endl;
    spaces = 0;
    cout << setw(numbers.length() + spaces) << numbers << '\n';
    spaces++;
    for(int i = 0; i < 4; i++) {
        cout << setw(reverse.length() + spaces) << reverse << setw(reverse.length() + spaces + 6) << numbers << endl;
        spaces += 2;
    }
    cout << setw(numbers.length() + spaces) << reverse << '\n';
    
    
    return 0;
}
