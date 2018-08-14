# Lab 1 Counting the Number of Words
The goal of this project is to implement an application to read words from a text file. The filename will be supplied onthe command line.  Your program should display the total number of words in the file.  (Consider a word to be a sequence of non-white-space characters.) 

# Lab 2 Sets and Arrays
Interface
* Interface to your abstract data type must provide the following operations:
  * return a pointer to a new set with a maximum capacity of *maxElts*
  * deallocate memory associated with the set pointed to by *sp*
  * return the number of elements in the set pointed to by *sp*
  * add elt to the set pointed to bysp
  * remove *elt* from the set pointed to by *sp*
  * if *elt* is present in the set pointed to by *sp* then return the matching element, otherwise return NULL
  * allocate and return an array of elements in the set pointed to by *sp*
* Implementation
  * You will write two different implementations of the data type for this assignment.  
  * First, implement a set using anunsorted array of length m>0, in which the first n≤m slots are used to hold n strings in some arbitrary order. Usesequential search to locate an element in the array.  
  * Second, implement a set using a sorted array of length m>0, in which the first n≤m slots are used to hold n strings in ascending order. Use binary search to locate an elementin the array.For both implementations, rather than duplicating the search logic in several functions, write an auxiliary function search that returns the location of an element in an array. Declaresearchas static so it is not visible outsidethe source file. Use search to implement the functions in the interface. Your implementation should allocatememory and copy the string when adding, and therefore also deallocate memory when removing.By the end of the first lab, you should have finished the first implementation.  You should verify that the ADT works with both test programs (unique, and thenparity) on all of the files.  
    * Note that unique takes an optionalsecond  file,  whose  words  it removes from  the  set,  thus  allowing  you  to  test  insertion  followed  by  deletion.   Incontrast, parity interweaves  insertion  and  deletion,  so  it  is  a  tougher  test. 

# Lab 3 Sets, Arrays, and Hash Tables
* The interface to your abstract data type must provide the following operations:
  * return a pointer to a new set with a maximum capacity of maxElts
  * deallocate memory associated with the set pointed to by sp
  * return the number of elements in the set pointed to by sp
  * add elt to the set pointed to by sp
  * remove elt from the set pointed to by sp
  * if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
  * allocate and return an array of elements in the set pointed to by sp
* Implementation
  * Implement a set using a hash table of length m>0 and linear probing to resolve collisions.  
  
# Lab 4 Hash Linked List
* Implement hashing with chaining, in each slot in the hash table is actually a linked list, allowing each slot to have infinite capacity and eliminating the need for probing.

# Lab 5 Heaps
* Implement heapsort and huffman coding.

# Lab 6 Quicksort
