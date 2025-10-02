#include"sllist.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

/*
 * Se puede crear una lista la cual tendra tamaño 0 
 * y no sera un NULL
 * */
void test_list_creation(void)
{
	sllist_t* lista = sllist_create();
	assert(lista != NULL);
	assert(sllist_length(lista) == 0);
	printf("\nEverithing is working as intended in %s\n", __func__);
}
/*
 * Test wheer or not you can add elements with the basic functions 
 * and wether or not you can retrieve those elements in order and 
 * wheter or not the functions are afecting the size of the list
 */
void test_list_modification(void)
{
	sllist_t* lista = sllist_create();
	int numbers[] = {1, 32, 2, 9};
	int num;
	sllist_push(lista, numbers[0]);
	sllist_push(lista, numbers[1]);
	assert(sllist_length(lista) == 2);
	sllist_append(lista, numbers[2]);
	sllist_append(lista, numbers[3]);
	assert(sllist_length(lista) == 4);
	num = (int*) sllist_get_at(2);
	assert(num == 2);
	printf("\nEverything working as intended on %s\n", __func__);
}

