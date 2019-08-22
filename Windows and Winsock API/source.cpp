#include "header.h"

int systemFunctions()
{
	int choice = 3;

	switch (choice)
	{
	case 1:
		screenSize();
		break;
	case 2:
		lockWorkStation();
		break;
	case 3:
		computerName();
		break;
	}
}

void screenSize()
{
	int x = 0, y = 0;
	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);
	wprintf(L"The screen size is: %dx%d\n", x, y);
}

int lockWorkStation()
{
	int r = LockWorkStation();
	if (r == 0) {
		wprintf(L"LockWorkStation() failed %d\n", GetLastError());
		return 1;
	}
}

int computerName()
{
	wchar_t computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	int r = GetComputerNameW(computerName, &size);
	if (r == 0) {
		wprintf(L"Failed to get computer name %ld", GetLastError());
		return 1;
	}
	wprintf(L"Computer name: %ls\n", computerName);
}