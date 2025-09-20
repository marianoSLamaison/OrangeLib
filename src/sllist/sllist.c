#include "sllist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct NODE {
	void * val;
	struct NODE * next;
};

typedef struct SIMPLE_LINKED_LIST{
	int length;
	struct NODE* head;
	struct NODE* tail;
}sllist;

sllist* sllist_create()
{
	sllist* ret = malloc(sizeof(sllist));
	ret->length = 0;
	ret->head = NULL;
	ret->tail = NULL;
	return ret;
}

int  sllist_get_length(sllist* list)
{
	return list->length;
}
struct NODE* get_at(sllist* list, int index)
{
	struct NODE* iter = list->head;
	int i=0;
	while (iter!= NULL)
	{
		if(i==index)
		{
			return iter;
		}
		iter = iter->next;
		i++;
	}
	return NULL;
}

void* sllist_get_elem(sllist* list, int index)
{
	struct NODE* nodo = get_at(list, index);	
	if (nodo == NULL)
		return NULL;
	return nodo->val;
}
void sllist_add(sllist* list, void* elem)
{
	struct NODE* newtail = malloc(sizeof(struct NODE));
	newtail->val = elem;
	newtail->next = NULL;
	if (list->length == 0)
	{
		list->head = newtail;
		list->tail = newtail;
		list->length++;
		return;
	}
	list->tail->next = newtail;
	list->tail = newtail;
	list->length++;
}
void sllist_add_at(sllist* list,void* elem, int index)
{
	struct NODE** passer = &list->head;
	struct NODE*  newLink = malloc(sizeof(struct NODE));
	int i = 0;
	newLink->val = elem;
	newLink->next = NULL;
	while(*passer != NULL) 
	{
		if (i==index)
		{	
			newLink->next = *passer;
			*passer = newLink;
			list->length++;
			return;
		}
		passer = &(*passer)->next;
		i++;
	}
	//llegamos al final de la lista
	*passer = newLink;
	list->tail = newLink;
	list->length++;
	return;
}
void sllist_eliminate(sllist* list, int index)
{
	sllist_eliminate_custom(list, index, free);
}
void sllist_eliminate_custom(sllist* list, int index, void (*destroyer)(void* elem))
{
	void* val = sllist_remove(list, index);
	if (val != NULL)
	{
		destroyer(val);
	}
}
struct NODE* _remove_(sllist* list, int index)
{
	struct NODE** passer = &(list->head);
	struct NODE* ret;
	int i=0;
	while((*passer) != NULL)
	{
		if (i==index)
		{
			ret = *passer;	
			(*passer) = (*passer)->next;
			list->length--;
			return ret;
		}
		passer = &((*passer)->next);
		i++;
	}
	return NULL;

}

void* sllist_remove(sllist* list, int index)
{
	struct NODE* nodo = _remove_(list, index);
	void* ret;
	if (nodo == NULL)
	{
		return NULL;
	}
	ret = nodo->val;
	free(nodo);
	return ret;
}
int  sllist_get_first_instance_index(sllist* list, void* elem, int (*cmp)(void* e1, void* e2))
{
	struct NODE* passer = list->head;
	int i=0;
	while (passer != NULL)
	{
		if (cmp(passer->val, elem)==0)
		{
			return i;
		}
		passer = passer->next;
		i++;
	}
	return -1;
}

int get_node_chain_length(struct NODE* nod)
{
	int i=0;
	while (nod != NULL)
	{
		i++;
		nod = nod->next;
	}
	return i;
}

struct NODE* ordered_merge_link_chain(struct NODE* a, struct NODE* b, int (*cmp)(void* e1, void* e2))
{
	struct NODE* holder;
	struct NODE* new_head;
	const int line_a = 1;
	const int line_b = -1;
	const int no_line = 0;
	int in_line = no_line;
	if (cmp(a->val, b->val)<0)
	{
		new_head = b;
		in_line = line_b;
	}
	else {
		new_head = a;
		in_line = line_a;
	}
	while (a != NULL && b != NULL)
	{
		if (cmp(a->val, b->val)<0)
		{
			if (in_line == line_a)
			{
				in_line = line_b;
				holder->next = b;
			}
			holder = b;
			b = b->next;
		} else {
			if (in_line == line_b)
			{
				in_line = line_a;
				holder->next = a;
			}
			holder = a;
			a = a->next;
		}
	}
	if (a == NULL) 
	{
		holder->next = b;
	}else if (b == NULL) 
	{
		holder->next = a;
	}
	return new_head;
}

void sllist_sorth(sllist* list, int (*cmp)(void* e1, void* e2))
{
	//partes
	//1. dividir la lista en un monton de listas de dos
	//2. ordenar esas listas de dos
	//3. mergear dichas listas en orden
	int list_length = sllist_get_length(list), lists_to_merge=0;
	struct NODE* nodos[list_length];
	struct NODE**iter = &(list->head);
	int i=0, sub_listas = (list_length / 2) + (list_length % 2) ; // que tantas sub listas
								   // se tendra que hacer
								   // al comienzo
	struct NODE* holder;
	while (*iter != NULL)
	{
		nodos[i] = *iter;
		iter = &((*iter)->next);
		i++;
	}
	for (i=0; i<list_length; i+=2) 
	{
		if (i== list_length - 1)
		{
			nodos[i]->next = NULL;
			//nodos[i/2] = nodos[i];
		}
		else if (cmp(nodos[i]->val,nodos[i+1]->val)<0)
		{
			nodos[i+1]->next = nodos[i];
			nodos[i]->next = NULL;
			holder= nodos[i+1];
			nodos[i+1]= nodos[i];
			nodos[i]=holder;
		} else {
			nodos[i]->next = nodos[i+1];
			nodos[i+1]->next = NULL;
		}
		nodos[i/2] = nodos[i];//lo movemos todo mas atras, con el fin de hacer mas vueltas
	}
	while (sub_listas > 1)
	{
		lists_to_merge = sub_listas;
		for (i=0; i<lists_to_merge; i+=2)
		{
			if (i != lists_to_merge - 1)
			{
				nodos[i] = ordered_merge_link_chain(
						nodos[i],
						nodos[i+1],
					cmp);
				sub_listas--;
			}	
			nodos[i/2] = nodos[i];
		}
	}
	//nodos[0] = ordered_merge_link_chain(nodos[0], nodos[1], cmp);
	//actualizamos la nueva lista
	list->length = get_node_chain_length(nodos[0]);
	list->head = nodos[0];
}
int  sllist_add_in_order(sllist* list, void* elem, int (*cmp)(void* e1, void* e2))
{
	struct NODE** iter = &(list->head);
	struct NODE* newIndex = malloc(sizeof(struct NODE));
	struct NODE* helper;
	int i=0;
	while (*iter != NULL) 
	{
		if (cmp((*iter)->val, elem) > 0)
		{
			newIndex->val = elem;
			helper = *iter;
			*iter = newIndex;
			newIndex->next = helper;
			return i;
		
		i++;
		iter = &((*iter)->next);
		}
	}
	*iter = newIndex;
	return i;
}
void sllist_destroy(sllist* list)
{
	sllist_destroy_custom(list, free);
}
void sllist_destroy_custom(sllist* list, void (*destroyer)(void* elem))
{
	struct NODE* iter = list->head;
	struct NODE* helper;
	while (iter != NULL)
	{
		destroyer(iter->val);
		helper = iter;
		iter = iter->next;
		free(helper);
	}
	free(list);
}

char* sllist_to_string(sllist* list, char* (*stringifier)(void*))
{
	int list_length = sllist_get_length(list), i, num_of_separators, total_string_size;
	const int num_de_llaves = 2;

	char**temp_list_of_strings = (char**)calloc(list_length, sizeof(char*));
	char* new_temp_entry;
	char* ret;
	num_of_separators = (list_length - 1);
	total_string_size = 0;
	
	for (i=0; i<list_length; i++)
	{
		new_temp_entry = stringifier(sllist_get_elem(list, i));
		temp_list_of_strings[i] = new_temp_entry;
		total_string_size += strlen(new_temp_entry);//sumamos el tamaño de todos los strings
	}
	//+1 por el character '\0' para que sea un string propiamente
	total_string_size += num_of_separators + num_de_llaves;
	ret = calloc(total_string_size + 1, sizeof(char));
	strcat(ret, "(");
	for (i=0; i<list_length; i++)
	{
		strcat(ret, temp_list_of_strings[i]);
		if (num_of_separators > 0)
		{
			strcat(ret, ";");
			num_of_separators--;
		}
		free(temp_list_of_strings[i]);
	}
	strcat(ret, ")");
	free(temp_list_of_strings);
	return ret;
}

