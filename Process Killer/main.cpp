#include <Windows.h>
#include <stdio.h>


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
int wmain(int argc, wchar_t** argv)
{
	LPCSTR lpClassName;
	//LPCSTR lpWindowName = "";
	wchar_t wcWindowName[100];

	printf("Enter window name for process to be terminated: ");
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
		printf("Error finding window: %ld\n", GetLastError());
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
	BOOL bInheritHandle = false;
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
		printf("Handle Not Created!\n");
	else
		printf("Handle Created!\n");

	DWORD dwExitCode;
	/*
	BOOL GetExitCodeProcess(
  HANDLE  hProcess,
  LPDWORD lpExitCode
);*/
	r = GetExitCodeProcess(hProcess, &dwExitCode);

	if (r == 0)
	{
		printf("Failed to retrieve termination status\n");
		printf("Error: %ld", GetLastError());
		return 1;
	}

	/*
	BOOL TerminateProcess(
  HANDLE hProcess,
  UINT   uExitCode
);*/
	r = TerminateProcess(hProcess, dwExitCode);

	if (r == 0)
	{
		printf("Termination Process Failed\n");
		printf("Error: %ld", GetLastError());
		return 1;
	}

	return 0;
}
