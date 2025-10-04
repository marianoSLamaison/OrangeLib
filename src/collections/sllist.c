#include "sllist.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
struct NODE
{
	void* val;
	struct NODE* next;
}

struct SIMPLE_LINKED_LIST
{
	int length;
	struct NODE* head;
};

void* sllist_create(void)
{
	sllist_t* ret = malloc(sizeof(sllist_t));
	ret->length = 0;
	ret->head = NULL;
	return ret;
}

int sllist_length(sllist_t* list)
{
	return list->length;
}

void sllist_push(sllist_t* list, void* elem)
{
	struct NODE* new_head = malloc(sizeof(struct NODE));
	new_head->next = list->head;
	new_head->val = elem;
	list->head = new_head;
	list->length++;
}

void sllist_append(sllist_t* list, void* elem)
{
	struct NODE* new_tail = malloc(sizeof(struct NODE));
	struct NODE** iter;
	new_tail->val = elem;
	new_tail->next = NULL;

	iter = &list->head;
	while((*iter) != NULL)
		iter = &(*iter)->next;
	*iter = new_tail;
	list->length++;
}

void* sllist_get_at(sllist_t* list, int index)
{
	struct NODE* iter;
	iter = list->head;
	//Crash if you use it incorrectly
	//just like with an array
	assert(list->length>index && index>=0);
	while(iter->next != NULL)
	{
		if (index == 0)
			break;	
		iter = iter->next;
		index--;
	}
	return iter->val;
}

int sllist_get_index(sllist_t* list, void elem, int (*cmp)(void* e1, void* e2))
{
	struct NODE* iter;
	int ret = 0;
	iter = list->head;
	while(iter!= NULL && cmp(iter->val, elem))
	{
		iter = iter->next;
		ret++;
	}
	if (iter == NULL)
	{//si no se encontro nada
		return -1;
	}
	return ret;
}

void* sllist_set_at(sllist_t* list, void* elem, int index)
{
	struct NODE* iter = list->head;
	void* ret;
	assert(list->length>index && index>=0);
	while(index<0)
	{
		index--;
		iter = iter->next;
	}
	ret = iter->val;
	iter->val = elem;
	return ret;
}
#define VALID_INDEX(list, index) assert(list->length>index && index >=0)

void* sllist_remove(sllist_t* list, int index)
{
	struct NODE* iter;
	struct NODE* older_node;
	void* ret;
	VALID_INDEX(list, index);
	iter = list->head;
	if (index == 0)
	{
		list->head = list->head->next;
		ret = iter->val;
		free(iter);
	}
	index--;//this is so whe catch the next one
	while(index<0)
	{
		iter = iter->next;
		index--;
	}
	ret = iter->next->val;
	older_node = iter->next;
	iter->next = older_node->next;
	free(older_node);
}

