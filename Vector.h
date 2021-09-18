#ifndef _VECTOR_FDFEFEY_
#define _VECTOR_FDFEFEY_
#include <stdbool.h>

typedef struct Item Item;
typedef struct Vector Vector;

struct Item
{
	const char* key;
	int value;
};

struct Vector
{
	Item* array;
	int size;
	int capacity;
};

Vector* CreateV();
void PushBack(Vector*, Item);
Item* GetValue(Vector* vector, int index);
void EraseV(Vector*);
bool RemoveV(Vector*, Item);

#endif