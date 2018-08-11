// FILE: random.cpp
// CLASS IMPLEMENTED: random (see random.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "random.h"

using namespace std;

namespace coen79_lab2
{
    // assign values to object based on parameters - parameterized constructor
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }
    
    void rand_gen::set_seed(int newSeed) {
        seed = newSeed;
    }
    
    int rand_gen::next() {
        seed = (multiplier * seed + increment) % modulus;
        return seed;
    }
    
    void rand_gen::print_info() const{
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
    }
}