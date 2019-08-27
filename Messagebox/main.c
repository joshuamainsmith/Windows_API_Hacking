#include <Windows.h>
#include <stdio.h>


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
int wmain(int argc, wchar_t** argv)
{
	LPCTSTR lpText = L"Message Goes Here";
	LPCTSTR lpCaption = L"Window Title Goes Here";
	int response = MessageBoxW(NULL, lpText, lpCaption, MB_OKCANCEL);

	int r = GetLastError();

	if (r != 0)
	{
		printf("Error getting handle: %ld", GetLastError());
		return 1;
	}

	if (response == 1)
		printf("Clicked OK\n");
	else if (response == 2)
		printf("User Exited\n");

	return 0;
}