//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init() {
        //Initializing pointers to NULL
        head_ptr = tail_ptr = cursor = precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence () {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source) {
        init();
        *this = source;
    }

    // Destructor
    sequence::~sequence() {
        list_clear(head_ptr);
        cursor = NULL, precursor = NULL, tail_ptr = NULL, head_ptr = NULL;
        many_nodes = 0;
    }

    // MODIFICATION MEMBER FUNCTIONS for the sequence class:
    void sequence::start( ) {
        cursor = head_ptr;
        precursor = NULL;
    }

    void sequence::end( ) {
        // case of empty list
        if(head_ptr == NULL && tail_ptr == NULL)
            return;
        cursor = tail_ptr;
        // case of only one item in list
        if(head_ptr == tail_ptr)
            precursor = NULL;
        else
            precursor = list_locate(head_ptr,many_nodes-1);
    }

    void sequence::advance( ) {
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }

    void sequence::insert(const value_type& entry) {
        // empty list or no current item
        if(precursor == NULL || !is_item()) {
            list_head_insert(head_ptr,entry);
            ++many_nodes;
            cursor = head_ptr;
            precursor = NULL;
            if(tail_ptr == NULL)
                tail_ptr = head_ptr;
            return;
        }
        list_insert(precursor,entry);
        cursor = precursor->link();
        ++many_nodes;
    }

    void sequence::attach(const value_type& entry) {
        if(!is_item()) {
            // no current item, empty list: attach at head
            if(head_ptr == NULL && tail_ptr == NULL) {
                list_head_insert(head_ptr,entry);
                cursor = head_ptr;
                precursor = NULL;
                tail_ptr = head_ptr;
                ++many_nodes;
                return;
            }
            // no current item, non-empty list: attach at end
            else {
                list_insert(precursor,entry);
                cursor = precursor->link();
                tail_ptr = tail_ptr->link();
                ++many_nodes;
                return;
            }
        }
        // store boolean in case tail needs to be updated
        bool updateTail(cursor == tail_ptr);
        precursor = cursor;
        list_insert(precursor,entry);
        cursor = cursor->link();
        // update tail if attached after tail
        if(updateTail)
            tail_ptr = tail_ptr->link();
        ++many_nodes;
    }
    
    void sequence::operator=(const sequence& source) {
        // check for self-assignment
        if(this == &source)
            return;
        list_clear(head_ptr);
        cursor = precursor = head_ptr = tail_ptr = NULL;
        
        many_nodes = 0;
        // empty list case
        if(source.cursor==NULL)
            list_copy(source.head_ptr, head_ptr, tail_ptr);  
        // cursor at head pointer
        else if(source.cursor==source.head_ptr) { 
            list_copy(source.head_ptr, head_ptr, tail_ptr); 
            start();
        }
        // cursor at tail pointer
        else if(source.cursor==source.tail_ptr) {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            end();
        } 
        // cursor somewhere in the middle
        else {
            // copy before precursor and then after
            list_piece(source.head_ptr, source.cursor, head_ptr, precursor);
            list_piece(source.cursor, NULL, cursor, tail_ptr);
            // link both list pieces
            precursor->set_link(cursor);
        }
        many_nodes = source.many_nodes;
    }

    void sequence::remove_current( ) {
        assert(is_item());
        // if cursor is at the head
        if(cursor == head_ptr) {
            // head is the only thing in the list
            if(head_ptr == tail_ptr) {
                list_head_remove(head_ptr);
                cursor = precursor = tail_ptr = head_ptr = NULL;
            }
            // there are other things in the list
            else {
                list_head_remove(head_ptr);
                cursor = head_ptr;
                precursor = NULL;
            }
        }
        // if cursor is at tail
        else if(cursor == tail_ptr) {
            list_remove(precursor);
            tail_ptr = precursor;
            precursor = cursor =  NULL;
        }
        // if cursor is somewhere in the middle
        else {
            list_remove(precursor);
            cursor = cursor->link();
        } 
        --many_nodes;
    }

    // CONSTANT MEMBER FUNCTIONS for the sequence class:
    size_t sequence::size( ) const {
        return many_nodes;
    }

    bool sequence::is_item( ) const {
        return(cursor != NULL);
    }

    sequence::value_type sequence::current( ) const {
        assert(is_item());
        return(cursor->data());
    }
}
