#ifndef _SLLIST_H_
#define _SLLIST_H_
/*
 * A implementation of a simple linked list or SLLIST 
 * that allows you to store items in it and to sorth it
 * The logit for how to implement this follows how godot's
 * array class works
 * */

//Basic struct of a list
typedef struct SIMPLE_LINKED_LIST sllist_t;

//Creates a new list returning a pointer to it
sllist_t* sllist_create(void);
//returns the length of a list
int sllist_length(sllist_t* list);
//adds an element at the begining of the list
void sllist_push(sllist_t* list, void* elem);
//adds an element at the very end of the list
void sllist_append(sllist_t* list, void* elem);
//returns the a certain item in the list
void* sllist_get_at(sllist_t* list, void* elem);
//returns the index of the first item that causes cmp to return 0
//or -1 if the item couldn't be found 
int sllist_get_index(sllist_t* list, void elem, int (*cmp)(void* e1, void* e2));
//Setea el velor de una entrada de la lista a un valor dado,
//retorna el valor previo
void* sllist_set_at(sllist_t* list, void* elem, int index);
//remueve un elemento de la lista reduciendo el tamaño de la misma
//si el elemento no existia no hace nada
void* sllist_remove(sllist_t* list, int index);
//borra cada elemento de la lista con la funcion "destroyer"
void sllist_clean(sllist_t* list, void (*destroyer)(void*));
//ordena la lista en orden dictado por cmp ( si retorna >0 se considera
//orden normal con 0 iguales y < 0 como en desorden
void sllist_sorth(sllist_t* list, int (*cmp)(void* e1, void* e2));
//retorna un string representando la lista entera
//usando la funcion to_string para cada elemento
//NOTE: It is expected for to_string to return an ansi string
//(one that finishes in '\0'
void sllist_to_string(sllist_t* list, char* (*to_string)(void* e));
//eliminates the whole list
void sllist_destroy(sllist_t* list, void (*destroyer)(void* e));
#endif
