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

void sllist_sorth(sllist* list, int (*cmp)(void* e1, void* e2))
{
	/*
	 * Necesito partirla en listas de 2, luego ordenarlas a todas 
	 * luego mergearlas en orden hasta tener una sola lista de nuevo
	 * */
	struct NODE* nodos[list->length];
	int size = list->length;
	int i = 0;
	int sublistas = 0;
	struct NODE** iter = &(list->head);
	struct NODE** jter = NULL;
	struct NODE* temp;
	if (size == 0) 
	{
		return;//mi logica se rompe al final con lista nula
	}
	while(*iter != NULL) 
	{//cargamos todos los valores en lista
		nodos[i] = (*iter);
		iter = &(*iter)->next;
		i++;
	}
	//ahora que estan todos en lista, ordenamos de a pares
	for (i=0; i<size; i+=2)//necesito iterar de a dos
	{
		if (size-i>=2)//si todavia quedan pares
		{
			if (cmp(nodos[i]->val, nodos[i+1]->val)<0)
			{
				temp = nodos[i];
				nodos[i] = nodos[i+1];
				nodos[i+1] = NULL;//la lista solo contiene las entradas a las sublistas
				nodos[i]->next = temp;
				temp->next = NULL;
			}else {

				//para poder iterarlos luego como si fueran listas en si
				nodos[i]->next = nodos[i+1];
				nodos[i+1]->next = NULL;
				nodos[i+1] = NULL;
			}
		} else {//solo queda un nodo que cargar
			nodos[i]->next = NULL;
		}
		nodos[i/2] = nodos[i];
		sublistas++;
	}
	//luego necesito mergear la lista de sublistas hasta que solo quede una lista
	for (i=0; sublistas > 1; i+=2)
	{
		//si la cantidad de listas adelante tuyo es suficiente para agarrar de a 2
		if (sublistas - i >= 2)
		{
			iter = nodos + i;
			jter = nodos + i + 1;
		
			while(*iter != NULL && *jter != NULL)
			{
				if (cmp((*iter)->val, (*jter)->val)<0)
				{
					temp = *jter;
					*jter = *iter;
					jter = &temp;
					iter = &(*iter)->next;//avanzamos iter para probar con el siguiente
					continue;
				}
				temp = (*iter)->next; 
				(*iter)->next = *jter;
				*iter = temp;

				temp = *iter;
				*iter = *jter;//hacemos que el anterior apunte a este
				iter = &(temp);
				jter = &(*jter)->next;//avanzamos jter para probar al siguiente
			}
			sublistas--;//mergee dos sublistas, por tanto hay una menos
		}
		//si no solamente movemos la lista un poco mas atras
		nodos[i/2] = nodos[i];//tis way we push them all to the bottom of the array
	//	nodos[i]=NULL;
	}
	list->head = *nodos;
	iter = nodos;
	while((*iter)->next != NULL)
	{
		iter = &(*iter)->next;
	}
	list->tail = *iter;
	//TODO: hacer un loop para obtener la cola
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

