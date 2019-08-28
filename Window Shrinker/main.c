#include <Windows.h>
#include <stdio.h>


//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
int wmain(int argc, wchar_t** argv)
{
	wchar_t wcWindowName[100];

	printf("Enter window to shrink: ");
	scanf("%[^\n]%*c", &wcWindowName);
	printf("Window Name: %s\n", wcWindowName);

	HWND hWnd = FindWindowA(NULL, (LPCSTR)wcWindowName);

	if (hWnd == NULL)
	{
		printf("Could not find window, error: %ld\n", GetLastError());
		return 1;
	}
	RECT lpRect;

	BOOL r = GetWindowRect(hWnd, &lpRect);

	if (r == FALSE)
	{
		printf("Failed to get window dimensions, error code: %ld\n", GetLastError());
		return 1;
	}

	printf("Left: %ld, Right: %ld, Bottom: %ld, Top: %ld\n", lpRect.left, lpRect.right, lpRect.bottom, lpRect.top);

	int cx = lpRect.right - lpRect.left;
	int cy = lpRect.bottom - lpRect.top;
	int cxHalf = cx * 0.66;

	while (cx > cxHalf)
	{
		r = SetWindowPos(hWnd, NULL, lpRect.left, lpRect.top, cx, cy, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
		cx -= 3;
		cy -= 3;
		if (r == FALSE)
		{
			printf("Failed to resize window, error code: %ld\n", GetLastError());
			return 1;
		}
	}

	return 0;
}