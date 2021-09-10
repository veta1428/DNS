#ifndef _HASH_TABLE_ABC_123
#define _HASH_TABLE_ABC_123

typedef struct HashTable HashTable;

HashTable* Create(int slots);
void Add(HashTable* hashTable, const char* key, int value);
int Get(HashTable* hashTable, const char* key);
void EraseHT(HashTable* hashTable);
int GetNumberOfItems(HashTable* hashTable);

#endif