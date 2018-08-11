#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "sequence1.h"

using namespace std;
/* Invariants of sequence class: 
 * 'used' is a member variable that stores the number of items in the sequence
 * If a sequence is empty, we don't care what is stored in the array 'data'
 * If a sequence is not empty, we only care what is stored from data[0] to data[used-1]
 * If there is a current item, it is at current_index. Otherwise, current_index = used
*/
namespace coen79_lab3 {
    sequence::value_type sequence::current() const {
        assert(is_item() == true);
        return data[current_index];
    }
    
    void sequence::advance(){
        if(is_item() == true)
	    current_index++;
    }

    void sequence::retreat() {
        if(current_index != 0)
            current_index--;
    }

    void sequence::insert(const sequence::value_type &entry) {
        assert(used < sequence::CAPACITY);
        // if the current index is empty, go to index 0
        if(!is_item())
            current_index = 0;
        // shift elements forward
        for(size_t i = used; i > current_index; --i) 
            data[i] = data[i-1];
        // insert element at current index and update used
        data[current_index] = entry;
        used++;
    }
    void sequence::attach(const sequence::value_type &entry) {
        assert(used < CAPACITY);
        // if current index is empty, go to last item
        if(!is_item())
            current_index = used-1;
            
            // shift elements forward
        for(size_t i = used; i > current_index; --i)
            data[i] = data[i-1];
        // insert entry, update current_index & used
            data[current_index+1] = entry;
        current_index++;
        used++;	
    }
    void sequence::remove_current() {
        assert(is_item() == true);
        // shift elements back
    	for(size_t i = current_index+1; i < used; i++)
            data[i-1] = data[i];
        used--;
        // update current_index
        if(current_index > used-1)
            current_index--;
    }

    void sequence::insert_front(const sequence::value_type &entry){
        assert(used < CAPACITY);
        // set current_index to 0 and insert
        start();
        insert(entry);
    }

    void sequence::attach_back(const sequence::value_type &entry) {
        assert(used < CAPACITY);
        // insert entry at the end of the list
        data[used] = entry;
        used++;
    }

    void sequence::remove_front() {
        assert(used > 0);
        // set current_index to 0 and then remove
        start();
        remove_current();
    }

    void sequence::operator+=(const sequence &rhs) {
        assert(used + rhs.size() < sequence::CAPACITY);
        // preserve size in a temporary variable
        // prevents a+=a from looping infinitely
        int temp = rhs.size();
        // copy items from rhs.data to this->data
        for(size_t i = 0; i < temp; i++) {
            data[used] = rhs.data[i];
            ++used;
        }
    }

    sequence operator+(const sequence &lhs, const sequence &rhs) {
        assert(lhs.size() + rhs.size() < sequence::CAPACITY);
        sequence s;
        // add elements from lhs and rhs
        s += lhs;
        s += rhs;
        return s;
    }
    
    sequence::value_type summation(sequence &s) {
        sequence::value_type sum = 0;
        // iterate through sequence and add each element
        for(s.start(); s.is_item(); s.advance())
            sum += s.current();
        return sum;
    }

    sequence::value_type sequence::operator[](int index) const {
        assert(index < used);
        return data[index];
    }
}
