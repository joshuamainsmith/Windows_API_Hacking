#include <Windows.h>
#include <stdio.h>

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
int wmain(int argc, wchar_t** argv)
{
	LPCSTR lpClassName;
	//LPCSTR lpWindowName = "";
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
		printf("[ERROR] Could Not Grab Privileged Handle to Token! Error Code: %ld", GetLastError());
	
	return 0;
}