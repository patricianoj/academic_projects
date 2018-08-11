//
//  part1.cpp
//  Lab 1
//
//  Created by Patricia Nataly Ornelas on 4/9/18.
//  Copyright © 2018 SCU. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cassert>

using namespace std;

/*
    precondition: a string of characters is inputted
    postcondition: the number of alphanumerican and
        non-alphanumerical characters (excluding spaces) is printed
*/

int main(int argc, const char * argv[]) {
    // take in string
    string input;
    cout << "Enter a string" << endl;
    getline(cin, input);
    
    // count characters in string by iterating from 0 to length of string
    int count_alpha = 0, count_nonalpha = 0;
    for(int i = 0; i < input.size(); i++) {
        // check if character is alphanumeric
        if(isalnum(input[i]))
            count_alpha++;
        // check that character is not a space
        else if(input[i] != ' ')
            count_nonalpha++;
    }
    
    // print results
    cout << input << " has " << count_alpha << " alphanumeric characters and " << count_nonalpha << " non-alphanumeric characters.\n";
    
    
    return 0;
}
