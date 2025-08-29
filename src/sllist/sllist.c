#include "sllist.h"
#include <stdlib.h>

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
void sllist_append(sllist* list, void* elem)
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
	struct NODE* passer = list->head;
	struct NODE* newLink = malloc(sizeof(struct NODE));
	int i = 0;
	newLink->val = elem;
	while(passer != NULL) 
	{
		if (i==index)
		{
			newLink->next = passer->next;
			passer->next = newLink;
			list->length++;
			return;
		}
		passer = passer->next;
		i++;
	}
	if (list->head == NULL)
		list->head = newLink;
	list->tail = newLink;
	newLink->next = NULL;
	list->length++;
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
struct NODE* remove(sllist* list, int index)
{
	struct NODE** passer = &list->head;
	struct NODE* handler;
	struct NODE* ret;
	int i=0;
	while((*passer) != NULL)
	{
		if (i==index)
		{
			ret = *passer;	
			handler = (*passer)->next;
			(*passer) = handler;
			return ret;
		}
		passer = &((*passer)->next);
		i++;
	}
	return NULL;

}

void*sllist_remove(sllist* list, int index)
{
	struct NODE* nodo = remove(list, index);
	void * ret;
	if (nodo == NULL)
		return NULL;
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
void* sllist_get_first_instance_of(sllist* list, void* elem, int (*cmp)(void* e1, void* e2))
{
	struct NODE* passer = list->head;
	int i=0;
	while (passer != NULL)
	{
		if (cmp(passer->val, elem)==0)
		{
			return passer->val;
		}
		passer = passer->next;
		i++;
	}
	return NULL;

}
/*
 * Retorna una lista de nodos que todos tienen otro nodo despues de este
 * osea basicamente retorna una lista de listas de dos o un nodo
 * */
sllist* split_in_twos(sllist* list)
{
	struct NODE* passer = list->head;
	struct NODE* holder;
	struct NODE* newEntry;
	sllist* ret = sllist_create();
	int i=0;
	while (passer != NULL) 
	{
		newEntry = malloc(sizeof(struct NODE));
		newEntry->val = passer;
		if (passer->next == NULL)
		{
			sllist_append(ret, newEntry);
			break;
		}
		passer = passer->next->next;
		sllist_append(ret, newEntry);
	}
	return ret;
}
//asuming you recieve two list that are perfectly sorted, it will 
//add all the elements from the second list to the first one in their 
//respective order
void merge_ordered_lists_in_order(struct NODE* list1, struct NODE* list2, int (*cmp)(void* e1, void* e2))
{
	struct NODE** iter = &list1;
	struct NODE*  jter = list2;
	struct NODE*  helper1;
	struct NODE*  helper2;
	while (*iter != NULL) 
	{
		if (cmp((*iter)->val, jter->val) > 0)
		{
			//put them in order
			//guardamos la direccion del objeto mayor
			helper1 = *iter;
			//colocamos al objeto menor en su posicion
			*iter = jter;
			//guardamos el objeto al que el objeto menor apuntaba
			helper2 = jter->next;
			//hacemos que el objeto menor apunte al objeto mayor
			jter->next = helper1;
			//cargamos el objeto siguiente de el iterador de la lista segunda
			jter = helper2;
		}else 
		{
			//avanzar el puntero
			iter = &(*iter)->next;
		}
	}
	//todos los elementos que queden en jter tienen que ser mayores que los elementos de iter
	//por tanto solo la pegas al final
	if (jter != NULL)
		*iter = jter;
}

void sllist_sorth(sllist* list, int (*cmp)(void* e1, void* e2))
{
	/*
	 * Necesito partirla en listas de 2, luego ordenarlas a todas 
	 * luego mergearlas en orden hasta tener una sola lista de nuevo
	 * */
	sllist* partitionedlist = split_in_twos(list);
	struct NODE* nodo = partitionedlist->head;
	struct NODE* handler;
	struct NODE* helper;
	//ordenamos las listas de dos
	while (nodo != NULL)
	{
		handler = nodo->val;
		if (cmp(handler->val, handler->next->val) > 0)
		{
			helper = handler->next;
			helper->next = handler;
			handler->next = NULL;
		}
	}
	if (partitionedlist->length==1)
	{
		//arreglar la lista original y volver, la cosa solo tenia dos elementos
	}
	handler = partitionedlist->head;
	while(partitionedlist->length>1)
	{
		helper = handler->val;
		merge_ordered_lists_in_order(handler->val, handler->next->val, cmp);
		helper = handler->next;
		handler->next = helper->next;
		free(helper);//destruimos el nodo que ya no usamos
		partitionedlist->length--;
	}
	list->head = partitionedlist->head->val;
	list->tail = get_at(partitionedlist, partitionedlist->length-1);
}
int  sllist_add_in_order(sllist* list, void* elem, int (*cmp)(void* e1, void* e2))
{
	struct NODE** iter = &list->head;
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
}
void sllist_destroy(sllist* list)
{
	sllist_destroy_custom(list, free);
}
void sllist_destroy_custom(sllist* list, void (*destroyer)(void* elem))
{
	struct NODE* iter;
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


