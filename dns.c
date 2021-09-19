
/*************************************************************************
   LAB 1                                                                

    Edit this file ONLY!

*************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>

#include "dns.h"
#include "Vector.h"
#include "HashTable.h"

#define MAX_DNS 10
#define MAX_SLOTS 10000

HashTable** hashTables = NULL;

typedef struct _DNS_ENTRY
{
    char* domainName;
    IPADDRESS    ip;
} DNS_ENTRY, * PDNS_ENTRY;

DNSHandle InitDNS( )
{
    if (hashTables == NULL)
    {
        hashTables = malloc(MAX_DNS * sizeof(HashTable*));
        memset(hashTables, 0, MAX_DNS * sizeof(HashTable*));

        hashTables[0] = Create(MAX_SLOTS);
        return (DNSHandle)1;
    }
    else 
    {
        for (size_t i = 0; i < MAX_DNS; i++)
        {
            if (hashTables[i] == NULL)
            {
                hashTables[i] = Create(MAX_SLOTS);
                return (DNSHandle) i + 1;
            }
        }
    }
    return (DNSHandle)0;  
}

void LoadHostsFile( DNSHandle hDNS, const char* hostsFilePath )
{
    HashTable* ht = hashTables[(int)hDNS - 1];
    FILE* fInput = NULL;

    fInput = fopen(hostsFilePath, "r");

    fseek(fInput, 0, SEEK_SET);

    char buffer[201];

    unsigned int uHostNameLength = 0;
    unsigned int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0;
    char* pStringWalker = &buffer[0];

    Item item;

    for (unsigned int i = 0; !feof(fInput); i++)
    {
        fscanf_s(fInput, "%d.%d.%d.%d %s", &ip1, &ip2, &ip3, &ip4, buffer, 200);
          
        item.value = (ip1 & 0xFF) << 24 |
            (ip2 & 0xFF) << 16 |
            (ip3 & 0xFF) << 8 |
            (ip4 & 0xFF);

        uHostNameLength = strlen(buffer);
  
        if (uHostNameLength)
        {
            item.key = (char*)malloc(uHostNameLength + 1);
            strcpy(item.key, pStringWalker);
        }

        Add(ht, item.key, item.value);
    }

    fclose(fInput);
}

IPADDRESS DnsLookUp( DNSHandle hDNS, const char* hostName )
{
    HashTable* ht = hashTables[(int)hDNS - 1];
    return Get(ht, hostName);
}

void ShutdownDNS( DNSHandle hDNS )
{
    HashTable* ht = hashTables[(int)hDNS - 1];
    EraseHT(ht);

    hashTables[(int)hDNS - 1] = NULL;
}
