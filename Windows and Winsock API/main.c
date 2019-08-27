#include "networking.h"		// winsock needs to be included before windows.h
#include "system.h"
#include "strings.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
{
	int choice = 2;

	switch (choice)
	{
	case 1:
		MessageBoxW(NULL, L"Влади́мир", L"Title", MB_OK);
		break;
	case 2:
		//systemFunctions(argc, argv);
		break;
	}

	return 0;
}

int wmain(int argc, wchar_t** argv)
{
	int choice = 4;

	switch (choice)
	{
	case 1:
		MessageBoxW(NULL, L"Влади́мир", L"Title", MB_OK);
		break;
	case 2:
		systemFunctions(argc, argv);
		break;
	case 3:
		networkingFunctions();
		break;
	case 4:
		stringFunctions();
		break;
	}

	return 0;
}

//	BOOL WINAPI SetWindowText(HWND, LPCTSTR); // changes the text of the specified window’s title bar.
//	BOOL WINAPI SetWindowTextA(HWND, LPCSTR);
//	BOOL WINAPI SetWindowTextW(HWND, LPCWSTR);
//
//	int WINAPI lstrlenW(LPCWSTR lpString); // The lstrlenW() function computes the length of a wide string
//
//	HWND WINAPI CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName,
//		LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth,
//		int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance,
//		LPVOID lpParam
//	); // used to create a window
//	
//	// We use the WriteConsoleW() function to write to the console in wide characters.
//
//	/*
//	The returned window handle is used by the SetWindowTextW() to set 
//	the title of the window
//	*/
//
//	/*
//	Data Types
//	 WORD
//	 DWORD
//	 DWORDLONG
//	 USHORT
//	 ULONG
//	 UCHAR
//	 UINT	
//	 VOID
//	 SHORT
//	 INT
//	 LONG
//	 FLOAT
//	 CHAR
//	*/
//
//
//	/*
//	Handles to Windows Resources
//	 HDC
//	 HFILE
//	 HCURSOR
//	 HFONT
//	 HICON
//
//	 HWND —handle to a window
//	 HPEN —handle to a pen
//	 HICON —handle to an icon
//	 HBITMAP —handle to a bitmap
//	 HBINSTANCE —handle to a program instance
//	 HBRUSH —handle to a brush
//	 HDC —handle to a device context
//	 HMENU —handle to a menu
//	 HFONT —handle to a font
//	 HFILE —handle to a file
//	 HCURSOR —handle to a cursor
//	*/
//
//	/*
//	Defined Macros
//	• COLORREF
//	• RGB
//	• HIWORD
//	• LOWORD
//	• MAKELPARAM
//	• MAKEWPARAM
//	*/
