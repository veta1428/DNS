#include "Vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const int INCREASE = 3;

Vector* CreateV()
{
	Vector* vec = malloc(sizeof(Vector));
	vec->capacity = 2;
	vec->array = malloc(vec->capacity * sizeof(Item));
	vec->size = 0;
	return vec;
}
void Resize(Vector* vector)
{
	vector->capacity *= INCREASE;
	Item* new_arr = malloc(vector->capacity * sizeof(Item));

	//copy
	for (size_t i = 0; i < vector->size; i++)
	{
		new_arr[i] = vector->array[i];
	}

	free(vector->array);
	vector->array = new_arr;
}
void PushBack(Vector* vector , Item item)
{
	if (vector->size == vector->capacity)
	{
		Resize(vector);
	}
	vector->array[vector->size] = item;
	vector->size++;
}


Item* GetValue(Vector* vector, int index)
{
	return &vector->array[index];
}
void EraseV(Vector* vector)
{
	for (size_t i = 0; i < vector->size; i++)
	{
		free(vector->array[i].key);
	}

	free(vector);

	vector = NULL;
}

bool RemoveV(Vector* vector, Item item)
{
	int index;
	for (size_t i = 0; i < vector->size; i++)
	{
		if ((vector->array[i].key == item.key) && (vector->array[i].value == item.value))
		{
			index = i;
			break;
		}
	}
	
}