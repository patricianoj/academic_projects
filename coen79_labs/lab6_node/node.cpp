// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
        const node *cursor;
        size_t answer;

        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            ++answer;

        return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }
    
    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
        list_clear(head_ptr);
        head_ptr = tail_ptr = NULL;
        // empty list case
        if(start_ptr == NULL)
            return;
        // insert head
        list_head_insert(head_ptr, start_ptr->data());
        tail_ptr = head_ptr;
        // only one item in list case
        if (start_ptr == end_ptr)
            return;
        start_ptr = start_ptr->link();
        // more than one item in list case
        while (start_ptr != end_ptr) {        
                list_insert(tail_ptr, start_ptr->data( ));
                if(tail_ptr->link() != end_ptr)
                    tail_ptr = tail_ptr->link( );
                start_ptr = start_ptr->link( );
        }
    }
   
    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
        size_t count = 0;
        const node *cursor;
        // set temporary pointer as cursor to iterate through list
        cursor = list_search(head_ptr, target);
        while(cursor != NULL) {
            ++count;
            cursor = cursor->link();
            // search for target
            cursor = list_search(cursor, target);
        }
        return count;
    }
  
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
        assert(position <= list_length(head_ptr)+1 && position > 0);
        node *target_node = head_ptr;
        // inserting at head
        if(position == 1) {
            list_head_insert(head_ptr,entry);
            return;
        }
        // iterate until position in linked list found
        for(int i = 1; i < position-1; i++)
            target_node = target_node->link();
        list_insert(target_node, entry);
    }

    node::value_type list_remove_at(node*& head_ptr, size_t position) {
        assert(position <= list_length(head_ptr)+1 && position > 0);
        node::value_type copy;
        node *target_node = head_ptr;
        // case removing head
        if(position == 1) {
            copy = head_ptr->data();
            list_head_remove(head_ptr);
            return copy;
        }
        // case of something in the middle
        for(int i = 1; i < position-1; i++)
            target_node = target_node->link();
        copy = target_node->data();
        list_remove(target_node);
        return copy;
    }

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
        assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
        node *new_head = NULL;
        // copy head
        list_head_insert(new_head,head_ptr->data());
        node *cursor = new_head;
        head_ptr = head_ptr->link();
        // copy the rest of the nodes if there are any
        for(size_t i = start+1; i < finish; i++) {
            list_insert(cursor,head_ptr->data());
            cursor = cursor->link();
            head_ptr = head_ptr->link();
        }
        return new_head;
    }

    void list_print (const node* head_ptr) {
        const node *tmp = head_ptr;
        while(tmp != NULL) {
            cout << tmp->data();
            // don't print comma if after tail pointer
            if(tmp->link() != NULL)
                cout << ", ";
            tmp = tmp->link();
        }
        cout << endl;
    }

    void list_remove_dups(node* head_ptr) {
        node *check = head_ptr;
        while(check != NULL) {
            node *tmp2 = check;
            while(tmp2->link() != NULL) {
                if(tmp2->link()->data() == check->data()) {
                    node *del = tmp2;
                    list_remove(del);
                }
                else
                    tmp2 = tmp2->link();
            }
            check = check->link();
        }
    }

    node* list_detect_loop (node* head_ptr) {
        node *slow_runner = head_ptr, *fast_runner = head_ptr;
        // iterate until the end of linked list
        while(fast_runner != NULL && fast_runner -> link() != NULL) {
            fast_runner = fast_runner->link()->link();
            slow_runner = slow_runner->link();
            // break if the two runners meet
            if(fast_runner == slow_runner)
                break;
        }
        // if runners never meet, return null
        if(fast_runner == NULL || fast_runner->link() == NULL)
            return NULL;
        // return the start of loop
        slow_runner = head_ptr;
        while(slow_runner != fast_runner) {
            fast_runner = fast_runner->link();
            slow_runner = slow_runner->link();
        }
        return fast_runner;
    }

}
