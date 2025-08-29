#include"sllist.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* printNumberList(sllist* list)
{
	int length = sllist_get_length(list);
	int i, handler;
	int numOfComas = length / 2; 
	const int digitsPerNum = 3;
	int totalRetLength = sizeof(char)*digitsPerNum+numOfComas;
	char* ret = malloc(totalRetLength + 1);//uno mas por el '\0'
	char* stringedNumber = malloc(digitsPerNum);
	ret[totalRetLength] = '\0';
	for (i=0; i<length; i++)
	{
		handler = *(int*)sllist_get_elem(list, i);
		sprintf(stringedNumber, "%d", handler);
		if (i>0)
			strcat(ret, ",");
		strcat(ret, stringedNumber);
	}
}

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

int main(void)
{
	sllist* lista = sllist_create();
	char val;
	TestLoadList(lista);

	printf("Hola");
	scanf("%d", &val);
	return 0;
}
