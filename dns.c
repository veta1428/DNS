
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
HashTable* ht;

typedef struct _DNS_ENTRY
{
    char* domainName;
    IPADDRESS    ip;
} DNS_ENTRY, * PDNS_ENTRY;

DNSHandle InitDNS( )
{
    ht = Create(10000);
    // IMPLEMENT ME =)
    return (DNSHandle)1;
		
    //return (DNSHandle)0;
}



void LoadHostsFile( DNSHandle hDNS, const char* hostsFilePath )
{
    // IMPLEMENT ME =)
    PDNS_ENTRY pDnsArra;
    PDNS_ENTRY* pDnsArray = &pDnsArra;
    int size;
    FILE* fInput = NULL;
    unsigned int dnCount = 0;
    unsigned int i = 0;

    
    fInput = fopen(hostsFilePath, "r");

    dnCount = getNumOfLines(fInput);

    if ((0 == dnCount) || !(*pDnsArray = (PDNS_ENTRY)calloc(dnCount, sizeof(DNS_ENTRY))))
    {
        fclose(fInput);     
    }

    size = dnCount;
    fseek(fInput, 0, SEEK_SET);

    for (i = 0; i < dnCount && !feof(fInput); i++)
    {
        char buffer[201] = { 0 };
        char* pStringWalker = &buffer[0];
        unsigned int uHostNameLength = 0;
        unsigned int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0;

        fgets(buffer, 200, fInput);
        if (5 != fscanf_s(fInput, "%d.%d.%d.%d %s", &ip1, &ip2, &ip3, &ip4, buffer, 200))
            continue;
        Item item;
        (*pDnsArray)[i].ip = (ip1 & 0xFF) << 24 |
            (ip2 & 0xFF) << 16 |
            (ip3 & 0xFF) << 8 |
            (ip4 & 0xFF);

        item.value = (*pDnsArray)[i].ip;
        uHostNameLength = strlen(buffer);
  
        if (uHostNameLength)
        {
            (*pDnsArray)[i].domainName = (char*)malloc(uHostNameLength + 1);
            item.key = (*pDnsArray)[i].domainName;
            strcpy((*pDnsArray)[i].domainName, pStringWalker);
        }
        Add(ht, item.key, item.value);
    }

    fclose(fInput);
   // return TRUE;
}



IPADDRESS DnsLookUp( DNSHandle hDNS, const char* hostName )
{
    return Get(ht, hostName);

    return INVALID_IP_ADDRESS;
}

void ShutdownDNS( DNSHandle hDNS )
{
    EraseHT(ht);
    // IMPLEMENT ME =)
}
