#include"sllist.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/*Es posible insertar valores cualquiera en la lista*/
void TestLoadList(sllist* list)
{
	int i;
	int * data;
	int vals[] = {3, 12, 0, 932, 1};
	for (i=0; i<5; i++)
	{	
		data = malloc(sizeof(int));
		*data = vals[i];
		sllist_add_at(list, data, i);
	}
}

char* number_to_sting(void* _num)
{
	int num = *(int*)_num;
	int num_digits = 0, num_holder = num;
	char* ret;
	char digit;
	const char inicio_de_digitos_ascii = 48;
	do {
		num_holder = num_holder / 10;
		num_digits++;
	}while ( num_holder != 0 );

	ret = (char*)calloc(num_digits + 1, sizeof(char));
	
	do {
		digit = num % 10;
		num /= 10;
		ret[num_digits-1] = digit + inicio_de_digitos_ascii;
		num_digits--;
	}while(num != 0);
	return ret;
}
/*Es posible remover un valor aleatorio de la lista*/
void test_remove_list(sllist* list)
{
	int* val = sllist_remove(list, 1);
	printf("El valor recuperado fue <%d>\n", *val);
	free(val);
	printf("Estado de la lista = %s\n", sllist_to_string(list, number_to_sting));
}
/*Es posible eliminar un elemento de la lista*/
void test_eliminate_list(sllist* list)
{
	sllist_eliminate(list, 2);
	printf("Estado de la lista = %s\n", sllist_to_string(list, number_to_sting));
}

int cmp_ints(void* a, void* b)
{
	return *(int*)b - *(int*)a;
}

void test_sllist_sort(sllist* list)
{
	sllist_sorth(list, cmp_ints);
	printf("\nEstado de la lista despues de sort = %s\n", sllist_to_string(list, number_to_sting));
}

int main(void)
{
	sllist* lista = sllist_create();
	int val;
	char* list_state;
	TestLoadList(lista);
	list_state = sllist_to_string(lista, number_to_sting);
	printf("El tamaño de la lista es <%d>\n", sllist_get_length(lista));
	printf("El estado de la lista es %s\n", list_state);
	//test_remove_list(lista);
	//test_eliminate_list(lista);
	test_sllist_sort(lista);
	
	scanf("%d", &val);
	return 0;
}
