#include "Vector.h"
#include "HashTable.h"
#include <stdint.h>

typedef Vector* Slot;

struct HashTable
{
	Slot* slots;
	int dataAmount;
	int slotsAmount;
};


//typedef Item HashTableItem;
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
uint64_t Hash(const char* key)
{
	uint64_t hash = FNV_OFFSET;
	for (const char* p = key; *p; p++) {
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
	}
	return hash;
}

HashTable* Create(int slots)
{
	HashTable* sh = malloc(sizeof(HashTable));
	//int a = sizeof(HashTable);
	sh->slots = malloc(slots * sizeof(Vector));
	//int b = sizeof(Vector);
	sh->slotsAmount = slots;
	for (size_t i = 0; i < slots; i++)
	{
		sh->slots[i] = CreateV();
	}
	return sh;
}

void Add(HashTable* hashTable, const char* key, int value)
{
	uint64_t hash = Hash(key);
	int index = hash % hashTable->slotsAmount;

	Item item;
	item.key = key;
	item.value = value;
	PushBack(hashTable->slots[index], item);
}

int Get(HashTable* hashTable, const char* key)
{
	uint64_t hash = Hash(key);
	int index = hash % hashTable->slotsAmount;
	Vector** vec = hashTable->slots;
	Vector* vector = vec[index];
	Item item;
	for (size_t i = 0; i < vector->size; i++)
	{
		item = *GetValue(vector, i);
		if (strcmp(item.key, key) == 0)
		{
			return item.value;
		}
	}
	return NULL;
}

void EraseHT(HashTable* hashTable)
{
	for (size_t i = 0; i < hashTable->slotsAmount; i++)
	{
		EraseV(hashTable->slots[i]);
	}
}

int GetNumberOfItems(HashTable* hashTable)
{
	return hashTable->dataAmount;
}



