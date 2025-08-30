#include"sllist.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


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

int main(void)
{
	sllist* lista = sllist_create();
	int val;
	char* list_state;
	TestLoadList(lista);
	list_state = sllist_to_string(lista, number_to_sting);
	printf("El tamaño de la lista es <%d>\n", sllist_get_length(lista));
	printf("El estado de la lista es %s\n", list_state);

	scanf("%d", &val);
	return 0;
}
