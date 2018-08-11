// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    statistician::statistician() {
        statistician::reset();
    }
    
    void statistician::next(double number) {
        total += number;
        // assign smallest and largest to the same number if empty
        if(count == 0) {
            smallest = number;
            largest = number;
        }
        // assign smallest and largest if number is
        //    smaller or larger respectively than current values
        else {
            if(number < smallest)
                smallest = number;
            if(number > largest)
                largest = number;
        }
        count++;
    }
    
    int statistician::length() const {
        return count;
    }
    
    double statistician::sum() const {
        return total;
    }
    
    double statistician::minimum() const {
        assert(count > 0);
        return smallest;
    }
    
    double statistician::maximum() const {
        assert(count > 0);
        return largest;
    }
    
    double statistician::mean() const {
        return(total/count);
    }
    
    void statistician::reset() {
        count = 0;
        total = 0;
    }
    
    bool operator ==(const statistician &s1, const statistician &s2) {
        // return true if both sequences are empty
        if(s1.length() == 0 & s2.length() == 0)
            return true;
        // return true if length, maximum, minimum, & mean are the same
        return(s1.length() == s2.length() && s1.minimum() == s2.minimum()
               && s1.mean() == s2.mean() && s1.maximum() == s2.maximum());
    }
    
    statistician operator *(double scale, const statistician &s) {
        // create new object
        statistician s1;
        s1.count = s.count;
        // if scale is positive, copy over scaled largest and smallest values
        if(scale > 0) {
            s1.smallest = s.smallest * scale;
            s1.largest = s.largest * scale;
        }
        // if scale is negative, swap largest and smallest
        else {
            s1.smallest = s.largest * scale;
            s1.largest = s.smallest * scale;
        }
        s1.total = s.total * scale;
        // return new object
        return s1;
    }
    
    statistician operator +(const statistician& s1, const statistician& s2) {
        // create new object
        statistician s3;
        s3.count = s1.count + s2.count;
        // assign smaller of the 2 smallest members
        if(s1.smallest < s2.smallest)
            s3.smallest = s1.smallest;
        else
            s3.smallest = s2.smallest;
        // assign larger of the 2 largest members
        if(s1.largest > s2.largest)
            s3.largest = s1.largest;
        else
            s3.largest = s2.largest;
        
        s3.total = s1.total + s2.total;
        return s3;
    }
}


