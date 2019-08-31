#include <Windows.h>
#include <stdio.h>

//typedef struct _PRIVILEGE_SET {
//	DWORD               PrivilegeCount;
//	DWORD               Control;
//	LUID_AND_ATTRIBUTES Privilege[ANYSIZE_ARRAY];
//} PRIVILEGE_SET, * PPRIVILEGE_SET;

//typedef struct _TOKEN_PRIVILEGES {
//	DWORD               PrivilegeCount;
//	LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
//} TOKEN_PRIVILEGES, * PTOKEN_PRIVILEGES;

int wmain(int argc, wchar_t** argv)
{
	LPCSTR lpClassName;
	wchar_t wcWindowName[100];

	printf("Enter window name to hook into: ");
	scanf("%[^\n]%*c", &wcWindowName);
	printf("Window Name: %s\n", wcWindowName);

	/*
	HWND FindWindowA(
  LPCSTR lpClassName,
  LPCSTR lpWindowName
);*/

	HWND hWnd = FindWindowA(NULL, (LPCSTR)wcWindowName);

	if (hWnd == NULL)
	{
		printf("Could not find window, error: %ld\n", GetLastError());
		return 1;
	}

	DWORD dwProcessId;

	/*
	DWORD GetWindowThreadProcessId(
	HWND    hWnd,
	LPDWORD lpdwProcessId
);*/
	DWORD dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);

	printf("Thread ID: %ld\n", dwThreadId);

	DWORD dwDesiredAccess = PROCESS_ALL_ACCESS;
	BOOL bInheritHandle = FALSE;
	/*
	HANDLE OpenProcess(
  DWORD dwDesiredAccess,
  BOOL  bInheritHandle,
  DWORD dwProcessId
);*/
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);

	int r = GetLastError();

	if (r != 0)
	{
		printf("Handle Not Created!\n");
		printf("Error: %ld", GetLastError());
		return 1;
	}

	if (hProcess <= 0)
		printf("Handle Not Created!, Error: %ld\n", GetLastError());
	else
		printf("Handle Created!\n");

	HANDLE ProcessHandle = hProcess;
	DWORD DesiredAccess = TOKEN_ALL_ACCESS;
	PHANDLE TokenHandle = NULL;

	r = OpenProcessToken(ProcessHandle, DesiredAccess, &TokenHandle);

	if (r > 0)
		printf("[INFO] Handle to Process Token Created! Token: %ld\n", TokenHandle);
	else
	{
		printf("[ERROR] Could Not Grab Privileged Handle to Token! Error Code: %ld", GetLastError());
		return 1;
	}

	PRIVILEGE_SET requiredPrivileges;
	requiredPrivileges.PrivilegeCount = 1;

	LPCWSTR lpSystemName = NULL;
	LPCWSTR lpName = L"SEDebugPrivilege";

	/*BOOL LookupPrivilegeValueA(
		LPCSTR lpSystemName,
		LPCSTR lpName,
		PLUID  lpLuid
	);*/

	r = LookupPrivilegeValueW(lpSystemName, lpName, &requiredPrivileges.Privilege->Luid);

	if (r != 0)
		printf("[INFO] Lookup For SEDebugPrivilege Worked...\n");
	else
	{
		printf("[ERROR] Lookup for SEDebugPrivilege Failed! Error Code: %ld", GetLastError());
		return 1;
	}

	LPBOOL pfResult = NULL;

	/*BOOL PrivilegeCheck(
		HANDLE         ClientToken,
		PPRIVILEGE_SET RequiredPrivileges,
		LPBOOL         pfResult
	);*/

	r = PrivilegeCheck(TokenHandle, &requiredPrivileges, &pfResult);

	if (r != 0)
		printf("[INFO] PrivilegeCheck Worked...\n");
	else
	{
		printf("[ERROR] PrivilegeCheck Failed! Error Code: %ld", GetLastError());
		return 1;
	}

	if (pfResult)
	{
		printf("[INFO] Privilege SEDebugPrivilege is Enabled...\n");
		requiredPrivileges.Privilege->Attributes = 0;
	}
	else
	{
		printf("[INFO] Privilege SEDebugPrivilege is NOT Enabled...\n");
		requiredPrivileges.Privilege->Attributes = SE_PRIVILEGE_ENABLED;
	}

	BOOL DisableAllPrivileges = FALSE;
	TOKEN_PRIVILEGES NewState;
	memset(&NewState, 0, sizeof NewState);
	DWORD BufferLength = sizeof(NewState);
	PTOKEN_PRIVILEGES PreviousState = NULL;
	PDWORD ReturnLength = NULL;

	NewState.PrivilegeCount = 1;
	*NewState.Privileges = *requiredPrivileges.Privilege;
	
	/*BOOL AdjustTokenPrivileges(
		HANDLE            TokenHandle,
		BOOL              DisableAllPrivileges,
		PTOKEN_PRIVILEGES NewState,
		DWORD             BufferLength,
		PTOKEN_PRIVILEGES PreviousState,
		PDWORD            ReturnLength
	);*/

	r = AdjustTokenPrivileges(TokenHandle, DisableAllPrivileges, &NewState, BufferLength, PreviousState, ReturnLength);

	if (r != 0)
		printf("[INFO] AdjustTokenPrivileges Flipped Privilege...\n");
	else
	{
		printf("[ERROR] AdjustTokenPrivileges Failed! Error Code: %ld", GetLastError());
		return 1;
	}

	return 0;
}