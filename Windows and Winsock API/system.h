#pragma once
#include <windows.h>
#include <wchar.h>
#include <Lmcons.h>
#include <VersionHelpers.h>
#include <initguid.h>
#include <KnownFolders.h>
#include <ShlObj.h>


#define BUFSIZE MAX_PATH

#pragma comment(lib, "user32.lib")

int systemFunctions(int, wchar_t**);
void screenSize();
int lockWorkStation();
int getComputerName();
int getUserName();
int setGetCurDir(int, wchar_t**);
int windowsVersion();
int memoryUsage();
int directoryPath();
int getDrivers();
int getDiskSpace();
int speedCPU();