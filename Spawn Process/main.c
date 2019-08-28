#include <Windows.h>
#include <stdio.h>

//typedef struct _PROCESS_INFORMATION {
//	HANDLE hProcess;
//	HANDLE hThread;
//	DWORD  dwProcessId;
//	DWORD  dwThreadId;
//} PROCESS_INFORMATION, * PPROCESS_INFORMATION, * LPPROCESS_INFORMATION;

//typedef struct _STARTUPINFOA {
//	DWORD  cb;
//	LPSTR  lpReserved;
//	LPSTR  lpDesktop;
//	LPSTR  lpTitle;
//	DWORD  dwX;
//	DWORD  dwY;
//	DWORD  dwXSize;
//	DWORD  dwYSize;
//	DWORD  dwXCountChars;
//	DWORD  dwYCountChars;
//	DWORD  dwFillAttribute;
//	DWORD  dwFlags;
//	WORD   wShowWindow;
//	WORD   cbReserved2;
//	LPBYTE lpReserved2;
//	HANDLE hStdInput;
//	HANDLE hStdOutput;
//	HANDLE hStdError;
//} STARTUPINFOA, * LPSTARTUPINFOA;

//typedef struct _STARTUPINFOW {
//	DWORD  cb;
//	LPWSTR lpReserved;
//	LPWSTR lpDesktop;
//	LPWSTR lpTitle;
//	DWORD  dwX;
//	DWORD  dwY;
//	DWORD  dwXSize;
//	DWORD  dwYSize;
//	DWORD  dwXCountChars;
//	DWORD  dwYCountChars;
//	DWORD  dwFillAttribute;
//	DWORD  dwFlags;
//	WORD   wShowWindow;
//	WORD   cbReserved2;
//	LPBYTE lpReserved2;
//	HANDLE hStdInput;
//	HANDLE hStdOutput;
//	HANDLE hStdError;
//} STARTUPINFOW, * LPSTARTUPINFOW;

//BOOL CreateProcessW(
//	LPCWSTR               lpApplicationName,
//	LPWSTR                lpCommandLine,
//	LPSECURITY_ATTRIBUTES lpProcessAttributes,
//	LPSECURITY_ATTRIBUTES lpThreadAttributes,
//	BOOL                  bInheritHandles,
//	DWORD                 dwCreationFlags,
//	LPVOID                lpEnvironment,
//	LPCWSTR               lpCurrentDirectory,
//	LPSTARTUPINFOW        lpStartupInfo,
//	LPPROCESS_INFORMATION lpProcessInformation
//);


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
int wmain(int argc, wchar_t** argv)
{
	PROCESS_INFORMATION lpProcessInformation;
	STARTUPINFOW lpStartupInfo;
	memset(&lpProcessInformation, 0, sizeof lpProcessInformation);
	memset(&lpStartupInfo, 0, sizeof lpStartupInfo);

	LPCWSTR lpApplicationName = L"C:\\Windows\\System32\\cmd.exe";
	LPWSTR lpCommandLine = NULL;
	LPSECURITY_ATTRIBUTES lpProcessAttributes = NULL;
	LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;
	LPVOID lpEnvironment = NULL;
	LPCWSTR lpCurrentDirectory = NULL;
	DWORD dwCreatedFlags = CREATE_NEW_CONSOLE;
	BOOL bInheritHandle = FALSE;

	lpStartupInfo.wShowWindow = STARTF_USESHOWWINDOW;
	lpStartupInfo.dwFlags = STARTF_USESHOWWINDOW;

	lpStartupInfo.cb = sizeof(lpStartupInfo);

	BOOL r = CreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandle, dwCreatedFlags,
		lpEnvironment, lpCurrentDirectory, &lpStartupInfo, &lpProcessInformation);

	if (r == 0)
	{
		printf("[ERROR] Could not Create Process! Error Code: %ld", GetLastError());
		return 1;
	}

	printf("[INFO] Process Created & Running...");

	return 0;
}