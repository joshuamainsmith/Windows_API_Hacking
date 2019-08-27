#include <Windows.h>
#include <stdio.h>


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
int wmain(int argc, wchar_t** argv)
{
	DWORD dwDesiredAccess = PROCESS_ALL_ACCESS;
	BOOL bInheritHandle = FALSE;
	printf("Enter PID: ");
	DWORD dwProcessId;// = 0x3B88;
	scanf_s("%ld", &dwProcessId);

	HANDLE hResponse = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);

	int r = GetLastError();

	if (r != 0)
	{
		printf("Handle Not Created!\n");
		printf("Error: %ld", GetLastError());
		return 1;
	}

	if (hResponse <= 0)
		printf("Handle Not Created!\n");
	else
		printf("Handle Created!\n");



	return 0;
}