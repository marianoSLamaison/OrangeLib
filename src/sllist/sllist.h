#ifndef SLLIST_H
#define SLLIST_H
/*
 * A list composed of "nodes" that point towards the next one in the chain
 * the functions that it uses work with stdlib.h unde the hood.
 * */
typedef struct SIMPLE_LINKED_LIST sllist;
/*
 * Returns a list of size 0 with 0 elements
 * */
sllist* sllist_create();
/*
 * Returns the length of a given list
 * */
int   sllist_get_length(sllist* list);
/*
 * Returns the item in the given position or NULL if the element was not in the list
 * */
void* sllist_get_elem(sllist* list, int index);
/*
 * Adds an item to the very end of the list
 * */
void sllist_add(sllist* list, void* elem);
/*
 * Adds an item at an especific position in the list, if the size of the list if smaller
 * then the given index it will only add the item at the very end of the list
 * */
void sllist_add_at(sllist* list,void* elem, int index);
/*
 * Eliminates an item from the list at a given position
 * if the index is bigger than the list itself, it does nothing
 * NOTE: this function only works as intended if the given object does not have 
 * pointers pointing to other memory directions. If the object do happen to have pointers
 * to other objects, then it is best to use "sllist_eliminate_custom" and provide a destroyer function
 * that can clean the object. Other wise the function may cause memory leaks.
 * */
void sllist_eliminate(sllist* list, int index);
/*
 * Function designed to provide a custom destroyer for objects that are pointing to other objects themselfs
 * */
void sllist_eliminate_custom(sllist* list, int index, void (*destroyer)(void* elem));
/*
 * Removes the object from the list and returns it. it returns -1 if the object couldn't be 
 * found and 0 otherwise
 * */
void* sllist_remove(sllist* list, int index);
/*
 * Finds the index of the first object in the list that makes cmp return 0.
 * cmp must retorn >0 if e1>e2, 0 if e1==e2 and <0 if e1<e2 the number itself does not matter
 * just it's sign
 * */
int  sllist_get_first_instance_index(sllist* list, void* elem, int (*cmp)(void* e1, void* e2));
/*
 * Uses the algorithm Merge Sort to sort a list of elements following the criteria given by
 * cmp
 * cmp must retorn >0 if e1>e2, 0 if e1==e2 and <0 if e1<e2 the number itself does not matter
 * just it's sign
 * */
void sllist_sorth(sllist* list, int (*cmp)(void* e1, void* e2));
/*
 * Adds an element in it's respective order 
 * NOTE: if the list is unordered it will only add the item in the first place that makes
 * cmp return <0.
 * cmp must retorn >0 if e1>e2, 0 if e1==e2 and <0 if e1<e2 the number itself does not matter
 * just it's sign
 * */
int  sllist_add_in_order(sllist* list, void* elem, int (*cmp)(void* e1, void* e2));
/*
 * Destroys the list, freeing all it's memory, asuming the elements inside do not
 * point towards other elements in memory
 * NOTE: if the elements do contain data that point towards other objects in memory that 
 * may not be inside this list and you wish to destroy them too, it will be better to use "sllist_destroy_custom"
 * and give it the detroyer function for the elements.
 * */
void sllist_destroy(sllist* list);
/*
 * Generalized version of "sllist_destroy" uses a destroyer function made by the user to know how to clean the objects
 * inside the list.
 * */
void sllist_destroy_custom(sllist* list, void (*destroyer)(void* elem));
/*
 * Returns a string that represents the given list, 
 * the string represents the elements based on the 
 * "stringifier" function given, and separates elements
 * with ';' and encloses all with "( )" 
 * NOTE: the char* returned by stringifier MUST be a string
 * (end with '\0') since this function uses string.h 
 * functions from the standar library.
 */
char* sllist_to_string(sllist* list, char* (*stringifier)(void*));

#endif
