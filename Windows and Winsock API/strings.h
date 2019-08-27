#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <strsafe.h>
#include <wchar.h>
#include <stdbool.h>
#include "Shlwapi.h"

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Shlwapi.lib")

#define STR_EQUAL 0
#define BUF_LEN 25
#define BUF_LEN2 8191
#define BUF_LEN3 256

int stringFunctions();
int ansiString();
int ansiString_s();
int stringLength();
int stringConcat();
int stringCase();
int stringCompare();
int stringFillBuff();
int stringTypes();
int shellTrim();
int shellConvert();
int shellSearch();
int safeLen();
int safeGets();
int safeCopy();
int safeConcat();
int safeFormat();