#include "Vector.h"
#include "HashTable.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef Vector* Slot;

struct HashTable
{
	Slot* slots;
	int dataAmount;
	int slotsAmount;
};

// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
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
	HashTable* hashTable = malloc(sizeof(HashTable));
	hashTable->slots = (Slot*) malloc(slots * sizeof(Vector));
	hashTable->slotsAmount = slots;

	for (size_t i = 0; i < slots; i++)
	{
	     hashTable->slots[i] = CreateV();
	}

	return hashTable;
}

void Add(HashTable* hashTable, const char* key, int value)
{
	uint64_t hash = Hash(key);
	int index = hash % hashTable->slotsAmount;

	Item item;
	item.key = key;
	item.value = value;

	PushBack(hashTable->slots[index], item);
	hashTable->dataAmount++;
}

int Get(HashTable* hashTable, const char* key)
{
	uint64_t hash = Hash(key);
	int index = hash % hashTable->slotsAmount;

	Item item;

	for (size_t i = 0; i < hashTable->slots[index]->size; i++)
	{
		item = *GetValue(hashTable->slots[index], i);
		if (strcmp(item.key, key) == 0)
		{
			return item.value;
		}
	}

	return NULL;
}

void EraseHT(HashTable* hashTable)
{
	//erase vectors (pointers to them)
	for (size_t i = 0; i < hashTable->slotsAmount; i++)
	{
		EraseV(hashTable->slots[i]);
	}
	
	//erase pointer to hashTable struct
	free(hashTable);

	hashTable = NULL;
}

int GetNumberOfItems(HashTable* hashTable)
{
	return hashTable->dataAmount;
}



