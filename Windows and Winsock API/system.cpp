#include "system.h"

int systemFunctions(int argc, wchar_t** argv)
{
	int choice = 11;
	switch (choice)
	{
	case 1:
		screenSize();
		break;
	case 2:
		lockWorkStation();
		break;
	case 3:
		getComputerName();
		break;
	case 4:
		getUserName();
		break;
	case 5:
		setGetCurDir(argc, argv);
		break;
	case 6:
		windowsVersion();
		break;
	case 7:
		memoryUsage();
		break;
	case 8:
		directoryPath();
		break;
	case 9:
		getDrivers();
		break;
	case 10:
		getDiskSpace();
		break;
	case 11:
		speedCPU();
		break;
	}

	return 0;
}

void screenSize()
{
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
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

int getComputerName()
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

int getUserName()
{
	wchar_t username[UNLEN + 1];
	DWORD len = sizeof(username) / sizeof(wchar_t);
	int r = GetUserNameW(username, &len);
	if (r == 0) {
		wprintf(L"Failed to get username %ld", GetLastError());
		return 1;
	}
	wprintf(L"User name: %ls\n", username);
}

int setGetCurDir(int argc, wchar_t **argv)
{
	wchar_t buf[BUFSIZE];
	if (argc != 2) {
		wprintf(L"Usage: %ls <dir>\n", argv[0]);
		return 1;
	}
	DWORD r = SetCurrentDirectoryW(argv[1]);
	if (r == 0) {
		wprintf(L"SetCurrentDirectoryW() failed (%ld)\n",
			GetLastError());
		return 1;
	}
	r = GetCurrentDirectoryW(BUFSIZE, buf);
	if (r == 0) {
		wprintf(L"GetCurrentDirectoryW() failed (%ld)\n",
			GetLastError());
		return 1;
	}
	if (r > BUFSIZE) {
		wprintf(L"Buffer too small; needs %d characters\n", r);
		return 1;
	}
	wprintf(L"Current directory is: %ls\n", buf);

	return 0;
}

int windowsVersion()
{	
	if (IsWindows10OrGreater()) {
		wprintf(L"This is Windows 10+");
	}
	else if (IsWindows8Point1OrGreater()) {
		wprintf(L"This is Windows 8.1\n");
	}
	else if (IsWindows8OrGreater()) {
		wprintf(L"This is Windows 8\n");
	}
	else if (IsWindows7OrGreater()) {
		wprintf(L"This is Windows 7\n");
	}
	else if (IsWindowsVistaOrGreater()) {
		wprintf(L"This is Windows Vista\n");
	}
	else if (IsWindowsXPOrGreater()) {
		wprintf(L"This is Windows XP\n");
	}

	return 0;
}

int memoryUsage()
{
	MEMORYSTATUSEX mem = { 0 };
	mem.dwLength = sizeof(mem);
	int r = GlobalMemoryStatusEx(&mem);
	if (r == 0) {
		wprintf(L"Failed to memory status %ld", GetLastError());
		return 1;
	}
	wprintf(L"Memory in use: %ld percent\n", mem.dwMemoryLoad);
	wprintf(L"Total physical memory: %lld\n", mem.ullTotalPhys);
	wprintf(L"Free physical memory: %lld\n", mem.ullAvailPhys);
	wprintf(L"Total virtual memory: %lld\n", mem.ullTotalVirtual);
	wprintf(L"Free virtual memory: %lld\n", mem.ullAvailVirtual);

	return 0;
}

int directoryPath()
{
	PWSTR path = NULL;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0,
		NULL, &path);
	if (SUCCEEDED(hr)) {
		wprintf(L"%ls\n", path);
	}
	CoTaskMemFree(path);

	return 0;
}

int getDrivers()
{
	wchar_t LogicalDrives[MAX_PATH] = { 0 };
	DWORD r = GetLogicalDriveStringsW(MAX_PATH, LogicalDrives);
	if (r == 0) {
		wprintf(L"Failed to get drive names %ld", GetLastError());
		return 1;
	}
	if (r > 0 && r <= MAX_PATH) {
		wchar_t* SingleDrive = LogicalDrives;
		while (*SingleDrive) {
			wprintf(L"%ls\n", SingleDrive);
			SingleDrive += wcslen(SingleDrive) + 1;
		}
	}

	return 0;
}

int getDiskSpace()
{
	unsigned __int64 freeCall, total, free;
	int r = GetDiskFreeSpaceExW(L"C:\\", (PULARGE_INTEGER)& freeCall,
		(PULARGE_INTEGER)& total, (PULARGE_INTEGER)& free);
	if (r == 0) {
		wprintf(L"Failed to get free disk space %ld", GetLastError());
		return 1;
	}
	wprintf(L"Available space to caller: %I64u MB\n",
		freeCall / (1024 * 1024));
	wprintf(L"Total space: %I64u MB\n", total / (1024 * 1024));
	wprintf(L"Free space on drive: %I64u MB\n", free / (1024 * 1024));

	return 0;
}

int speedCPU()
{
	DWORD BufSize = MAX_PATH;
	DWORD mhz = MAX_PATH;
	HKEY key;
	long r = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
		L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
		KEY_READ, &key);
	if (r != ERROR_SUCCESS) {
		wprintf(L"RegOpenKeyExW() failed %ld", GetLastError());
		return 1;
	}
	r = RegQueryValueExW(key, L"~MHz", NULL, NULL, (LPBYTE)& mhz,
		&BufSize);
	if (r != ERROR_SUCCESS) {
		wprintf(L"RegQueryValueExW() failed %ld", GetLastError());
		return 1;
	}

	wprintf(L"CPU speed: %lu MHz\n", mhz);
	r = RegCloseKey(key);
	if (r != ERROR_SUCCESS) {
		wprintf(L"Failed to close registry handle %ld",
			GetLastError());
		return 1;
	}

	return 0;
}
