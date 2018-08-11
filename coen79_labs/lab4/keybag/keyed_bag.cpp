//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---

#include <iostream>
#include "keyed_bag.h"
#include <cstdlib>  // Provides size_t
#include <string>
#include <cassert>

using namespace std;
using coen79_lab4::keyed_bag;

// modification member functions
void keyed_bag::erase() {
    used = 0;
}
bool keyed_bag::erase(const key_type& key) {
    if(!has_key(key))
        return false;
    for(int i = 0; i < used; ++i) {
        if(keys[i] == key) {
            // shift elements back
            for(int j = i; j < used-1; j++) {
                keys[j] = keys[j+1];
                data[j] = data[j+1];
            }
            used--;
            return true;
        }
    }
    return true;
}
void keyed_bag::insert(const keyed_bag::value_type& entry, const key_type& key) {
    assert(size() < CAPACITY && !has_key(key));
    keys[used] = key;
    data[used] = entry;
    used++;
}

void keyed_bag::operator +=(const keyed_bag& addend) {
    assert(addend.size() + size() <= CAPACITY);
    int temp = addend.size();
    // update keys and data array
    for(int i = 0; i < temp; i++) {
        keys[used] = addend.keys[i];
        data[used] = addend.data[i];
        used++;
    }
}

bool keyed_bag::has_key(const key_type& key) const {
    for(int i = 0; i < used; ++i) {
    	if(keys[i] == key)
            return true;
    }
    return false;
}

keyed_bag::value_type keyed_bag::get(const key_type& key) const {
    assert(has_key(key));
    for(int i = 0; i < used; ++i) {
        if(keys[i] == key)
            return data[i];
    }
    return 0;
}

keyed_bag::size_type keyed_bag::size( ) const {
    return used;
}

keyed_bag::size_type keyed_bag::count(const keyed_bag::value_type& target) const {
    keyed_bag::size_type count = 0;
    for(int i = 0; i < used; ++i) {
        if(data[i] == target)
            count++;
    }
    return count;
}
bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
    for(int i = 0; i < used; ++i) {
        if(otherBag.has_key(keys[i]))
            return true;
    }
    return false;
}

// NON-MEMBER FUNCTIONS
namespace coen79_lab4 {
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        assert((b1.size() + b2.size() <= keyed_bag::CAPACITY) && !(b1.hasDuplicateKey(b2)));
        keyed_bag n;
        n += b1;
        n += b2;
        return n;
    }
}
