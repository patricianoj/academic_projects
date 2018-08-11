#include <cstdlib> 
#include <iostream>
#include <cstring>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include "mystring.h"

/* Invariants of Class
 * characters points to a dynamic array in which the string is stored as a null-terminated string
 * allocated is the member variable that holds the total length of the dynamic array
 * current_length is the number of characters prior to the null character
 */

namespace coen79_lab5 {
    // CONSTRUCTOR, COPY CONSTRUCTOR, and DECONSTRUCTOR
    string::string(const char str[ ]) {
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
	    // copy array passed as parameter into private member variable
        std::strncpy(characters, str, current_length);
    }
    string::string(char c) {
        current_length = 1;
        allocated = current_length+1;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
    }
    string::string(const string& source) {
        current_length = source.current_length;
        allocated = current_length + 1;
        characters = new char[allocated];
        // copy the individual characters from the parameter
        for(int i = 0; i < source.current_length; ++i)
            characters[i] = source.characters[i];
    }
    string::~string( ) {
	// deallocate memory
        delete [] characters;
        characters = NULL;
        allocated = 0, current_length = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS
    void string::operator +=(const string& addend) {
        *this += addend.characters;
    }
    void string::operator +=(const char addend[ ]) {
        // ensure that parameter is NULL-terminated
        assert(addend[strlen(addend)] == '\0');
        // allocate more memory if necessary
        if(current_length + std::strlen(addend) > allocated)
            reserve(current_length + strlen(addend)+1);
        // copy characters from parameter into private member variable
        // increment current_length accordingly
        for(int i = 0; i < strlen(addend); ++i) {
            characters[current_length] = addend[i];
            current_length++;
        }
        characters[current_length] = '\0';
    }
    void string::operator +=(char addend) {
        // allocate more memory if necessary
        if(current_length + 1 > allocated)
            reserve(current_length+1);
        // add character and increment current_length
        characters[current_length] = addend;
        current_length++;
        characters[current_length] = '\0';
    }
    void string::reserve(size_t n) {
        // copy over memory into new array
        char *temp_str;
        if(n == allocated)
            return;
        if(n < current_length+1)
            n = current_length+1;
        
        temp_str = new char[n];
        
        strncpy(temp_str, characters, n);
        // delete old array and set it to new array
        delete [] characters;
        characters = temp_str;
        
        allocated = n+1;
    }
    string& string::operator=(const string& source) {
        // check for self-assignment
        if(this == &source)
            return *this;
        // allocate more memory if necessary
        if(source.current_length > allocated)
            reserve(source.current_length+1);
        // copy over member variables
        for(int i = 0; i <= source.current_length; ++i)
            characters[i] = source.characters[i];
        current_length = source.current_length;
        characters[current_length] = '\0';
        return *this;
    }
    void string::insert(const string& source, unsigned int position) {
        assert(position <= current_length);
        // reserve if source string greater than current length
        if(allocated < (current_length + source.current_length))
            reserve(current_length + source.current_length);
        // shift characters to the right of position
        for(int i = current_length; i > position; --i)
            characters[i] = characters[i-1];
        // copy string before postion
        for(int i = 0; i < source.current_length; ++i)
            characters[position+i] = source.characters[i];
        current_length = current_length + source.current_length;
    }
    void string::dlt(unsigned int position, unsigned int num) {
        assert((position + num) <= current_length);
        // shift characters to the left
        for(int i = position; i < current_length; ++i)
            characters[i] = characters[num+i];
        current_length -= num;
    }
    
    
    
    
    void string::replace(char c, unsigned int position) {
        assert(position <= current_length);
        characters[position] = c;
    }
    void string::replace(const string& source, unsigned int position) {
        assert((position + source.length()) <= current_length);
        // replace characters from position to the end of the length of source
        for(int i = 0; i < source.length(); ++i) {
            characters[position] = source.characters[i];
            position++;
        }
    }

    // CONSTANT MEMBER FUNCTIONS
    char string::operator [ ](size_t position) const {
        assert(position < current_length);
        return characters[position];
    }
    int string::search(char c) const {
        for(int i = 0; i < current_length; ++i) {
            if(characters[i] == c)
                return i;
        }
        return -1;
    }
    int string::search(const string& substring) const {
        int found = 0;
        for(int i = 0; i < current_length; ++i) {
            // check that index doesn't pass current_length
            if(i + substring.current_length <= current_length) {
                // count how many characters of substring are found
                for(int j = 0; j < substring.current_length; ++j) {
                    if(characters[i+j] == substring.characters[j])
                        found++;
                }
                if(found == substring.current_length)
                    return i;
            }
            // reset count
            found = 0;
        }
        return -1;
    }
    unsigned int string::count(char c) const {
        int count = 0;
        // iterate through characters and increment count every time c found
        for(int i = 0; i < current_length; ++i) {
            if(characters[i] == c)
                count++;
        }
        return count;
    }

    // FRIEND FUNCTIONS
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        for(int i = 0; i < source.current_length; ++i) {
            outs << source.characters[i];
        }
        return outs;
    }
    
    bool operator ==(const string& s1, const string& s2) {
        // if the lengths are different, return false
        if(s1.current_length != s2.current_length)
            return false;
        // iterate and look for any differences in characters
        for(int i = 0; i < s1.current_length; ++i) {
            if(s1.characters[i] != s2.characters[i])
                return false;
        }
        return true;
    }
    
    bool operator !=(const string& s1, const string& s2) {
        // if the lengths are different, return true
        if(s1.current_length != s2.current_length)
            return true;
        // if there are any differences in the arrays, return true
        for(int i = 0; i < s1.current_length; ++i) {
            if(s1.characters[i] != s2.characters[i])
                return true;
        }
        return false;
    }
    bool operator > (const string& s1, const string& s2) {
        return(strcmp(s1.characters,s2.characters) > 0);
    }
    bool operator < (const string& s1, const string& s2) {
        return(strcmp(s1.characters,s2.characters) < 0);
    }
    bool operator >=(const string& s1, const string& s2){
        return(strcmp(s1.characters,s2.characters) >= 0);
    }
    bool operator <=(const string& s1, const string& s2){
        return(strcmp(s1.characters,s2.characters) <= 0);
    }

    // NON-MEMBER FUNCTIONS for the string class
    string operator +(const string& s1, const string& s2) {
        string n;
        n += s1;
        n += s2;
        return n;
    }
    string operator +(const string& s1, const char addend[ ]) {
        string n;
        n += s1;
        n += addend;
        return n;
    }
    std::istream& operator >> (std::istream& ins, string& target) {
        target = "";
        char p;
        // skip leading spaces
        while(!ins.eof() && isspace(ins.peek()))
            ins.ignore();
        // add to target until eof or a space is hit
        while(!ins.eof() && !isspace(ins.peek()))  {
            ins >> p;
            target += p;
        }
        return ins;
    }
    
}
