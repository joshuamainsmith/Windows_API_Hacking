#include <Windows.h>
#include <stdio.h>
#include <WinDNS.h>


typedef struct _DNS_CACHE_ENTRY
{
	struct _DNS_CACHE_ENTRY* pNext; // Pointer to next entry
	LPWSTR recName; // DNS Record Name
	DWORD wType; // DNS Record Type
	DWORD wDataLength; // Not referenced
	DWORD dwFlags; // DNS Record Flags
} DNSCACHEENTRY, * PDNSCACHEENTRY;


typedef int(WINAPI* DNS_GET_CACHE_DATA_TABLE)(PDNSCACHEENTRY);
int wmain(int argc, wchar_t** argv)
{
	PDNSCACHEENTRY DNS_Entry = (PDNSCACHEENTRY)malloc(sizeof(DNSCACHEENTRY));

	HINSTANCE hLib = LoadLibrary(TEXT("DNSAPI.dll"));
	DNS_GET_CACHE_DATA_TABLE DnsGetCacheDataTable =
		(DNS_GET_CACHE_DATA_TABLE)GetProcAddress(hLib, "DnsGetCacheDataTable");

	DWORD r = DnsGetCacheDataTable(DNS_Entry);

	if (r == 0)
	{
		printf("[ERROR] Failed to get DNS Cache Table.. Error Code: %ld", GetLastError());
		return 1;
	}

	printf("[INFO] Got DNS Cache Table, Parsing Data...\n");
	DNS_Entry = DNS_Entry->pNext;

	while (DNS_Entry->pNext)
	{
		printf("[INFO] DNS Entry: %ls - Type: %d\n", DNS_Entry->recName, DNS_Entry->wType);
		DNS_Entry = DNS_Entry->pNext;
	}
	
	printf("[INFO] DNS Entry: %ls - Type: %d\n", DNS_Entry->recName, DNS_Entry->wType);

	printf("[INFO] DNS Cache Table Dumped\n");

	return 0;
}
