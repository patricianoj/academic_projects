//
//  part3.cpp
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
    precondition: a text file
    postcondition: prints all words with more than 10 letters in uppercase
*/
 
int main(int argc, const char * argv[]) {
    // check that file was given as input
    assert(argc > 0);
    
    // open file and assert it was able to open
    ifstream infile;
    infile.open(argv[1]);
    assert(!infile.fail());
    
    int count;
    string word;
    
    // iterate through every word of file until end of file
    while(!infile.eof()) {
        infile >> word;
        count = 0;
        for(int i = 0; i < word.size(); i++) {
            // increase count if character is a letter
            if(!ispunct(word[i])) {
                count++;
                // make letter uppercase
                if(islower(word[i]))
                    word[i] = toupper(word[i]);
            }
            // remove punctuation
            else
                word.erase(i--,1);
        }
        // print string if length is more than 10
        if(count >= 10) {
            cout << word << endl;
        }
    }
    
    // close file
    infile.close();

    return 0;
}
