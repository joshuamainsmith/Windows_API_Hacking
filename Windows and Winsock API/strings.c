#include "strings.h"

int stringFunctions()
{
	int choice = 16;

	switch (choice)
	{
	case 1:
		ansiString();
		break;
	case 2:
		ansiString_s();
		break;
	case 3:
		stringLength();
		break;
	case 4:
		stringConcat();
		break;
	case 5:
		stringCase();
		break;
	case 6:
		stringCompare();
		break;
	case 7:
		stringFillBuff();
		break;
	case 8:
		stringTypes();
		break;
	case 9:
		shellTrim();
		break;
	case 10:
		shellConvert();
		break;
	case 11:
		shellSearch();
		break;
	case 12:
		safeLen();
		break;
	case 13:
		safeGets();
		break;
	case 14:
		safeCopy();
		break;
	case 15:
		safeConcat();
		break;
	case 16:
		safeFormat();
		break;
	}

	return 0;
}

int ansiString()
{
	wchar_t str1[] = L"There are 15 pines";
	wprintf(L"The length of the string is %d characters\n",
		wcslen(str1));
	wchar_t buf[20];
	wcscpy(buf, L"Wuthering");
	wcscat(buf, L" heights\n");
	wprintf(buf);
	if (wcscmp(L"rain", L"rainy") == STR_EQUAL) {
		wprintf(L"rain and rainy are equal strings\n");
	}
	else {
		wprintf(L"rain and rainy are not equal strings\n");
	}
	return 0;
}

int ansiString_s()
{
	wchar_t str1[] = L"There are 15 pines";
	const int MAX_CHARS = 50;
	size_t count = wcsnlen_s(str1, MAX_CHARS);
	wprintf(L"The length of the string is %ld characters\n", count);
	wchar_t buf[BUF_LEN] = { 0 };
	int r = wcscpy_s(buf, BUF_LEN, L"Wuthering");
	if (r != 0) {
		wprintf(L"wcscpy_s() failed %ld", r);
	}
	r = wcscat_s(buf, BUF_LEN, L" heights\n");
	if (r != 0) {
		wprintf(L"wcscat_s() failed %ld", r);
	}
	wprintf_s(buf);

	return 0;
}

int stringLength()
{
	char* name = "Jane";
	wchar_t* town = L"Bratislava";
	wprintf(L"The length of the name string is %d\n", lstrlenA(name));
	wprintf(L"The town string length is %d\n", lstrlenW(town));

	return 0;
}

int stringConcat()
{
	wchar_t* s1 = L"ZetCode, ";
	wchar_t* s2 = L"tutorials ";
	wchar_t* s3 = L"for ";
	wchar_t* s4 = L"programmers.\n";
	int len = lstrlenW(s1) + lstrlenW(s2)
		+ lstrlenW(s3) + lstrlenW(s4);
	wchar_t buf[100];
	lstrcpyW(buf, s1);
	lstrcatW(buf, s2);
	lstrcatW(buf, s3);
	lstrcatW(buf, s4);
	wprintf(buf);

	return 0;
}

int stringCase()
{
	wchar_t str[] = L"Europa";
	CharLowerW(str);
	wprintf(L"%ls\n", str);
	CharUpperW(str);
	wprintf(L"%ls\n", str);

	return 0;
}

int stringCompare()
{
	wchar_t* s1 = L"Strong";
	wchar_t* s2 = L"strong";
	if (lstrcmpW(s1, s2) == STR_EQUAL) {
		wprintf(L"%ls and %ls are equal\n", s1, s2);
	}
	else {
		wprintf(L"%ls and %ls are not equal\n", s1, s2);
	}
	wprintf(L"When applying case insensitive comparison:\n");
	if (lstrcmpiW(s1, s2) == STR_EQUAL) {
		wprintf(L"%ls and %ls are equal\n", s1, s2);
	}
	else {
		wprintf(L"%ls and %ls are not equal\n", s1, s2);
	}

	return 0;
}

int stringFillBuff()
{
	SYSTEMTIME st = { 0 };
	wchar_t buf[128] = { 0 };
	GetLocalTime(&st);
	wsprintfW(buf, L"Today is %lu.%lu.%lu\n", st.wDay,
		st.wMonth, st.wYear);
	wprintf(buf);

	return 0;
}

int stringTypes()
{
	wchar_t str[] = L"7 white, 3 red roses.\n";
	int alphas = 0;
	int digits = 0;
	int spaces = 0;
	int puncts = 0;
	int contrs = 0;
	int size = lstrlenW(str);
	WORD types[sizeof str];
	ZeroMemory(types, size);
	bool rv = GetStringTypeW(CT_CTYPE1, str, size, types);
	if (!rv) {
		wprintf(L"Could not get character types (%ld)",
			GetLastError());
		return EXIT_FAILURE;
	}
	for (int i = 0; i < size; i++) {
		if (types[i] & C1_ALPHA) {
			alphas++;
		}
		if (types[i] & C1_DIGIT) {
			digits++;
		}
		if (types[i] & C1_SPACE) {
			spaces++;
		}
		if (types[i] & C1_PUNCT) {
			puncts++;
		}
		if (types[i] & C1_CNTRL) {
			contrs++;
		}
	}
	wprintf(L"There are %ld letter(s), %ld digit(s), "
		L"%ld space(s), %ld punctuation character(s), "
		L"and %ld control character(s)\n", alphas, digits,
		spaces, puncts, contrs);

	return 0;
}

int shellTrim()
{
	wchar_t buf[] = L"23tennis74";
	wchar_t trim[] = L"0123456789";
	wprintf(L"Original string: %ls\n", buf);
	bool r = StrTrimW(buf, trim);
	if (r == true) {
		wprintf(L"The StrTrim() trimmed some characters\n");
	}
	else {
		wprintf(L"No characters were trimmed\n");
	}
	wprintf(L"Trimmed string: %ls\n", buf);

	return 0;
}

int shellConvert()
{
	wchar_t str1[] = L"512";
	wchar_t str2[] = L"0xAB12";
	int n = 0;
	bool r = StrToIntExW(str1, STIF_DEFAULT, &n);
	if (r == true) {
		wprintf(L"The value is %d\n", n);
	}
	else {
		wprintf(L"The first conversion failed\n");
		return 1;
	}
	r = StrToIntExW(str2, STIF_SUPPORT_HEX, &n);
	if (r == true) {
		wprintf(L"The value is %d\n", n);
	}
	else {
		wprintf(L"The second conversion failed\n");
		return 1;
	}

	return 0;
}

int shellSearch()
{
	wchar_t buf[] = L"Today is a rainy day.";
	wchar_t* search_word = L"rainy";
	int len = wcslen(search_word);
	LPWSTR pr = StrStrW(buf, search_word);
	if (pr == NULL) {
		wprintf(L"No match\n");
	}
	else {
		wprintf(L"%.*ls is found\n", len, pr);
	}

	return 0;
}

int safeLen()
{
	wchar_t str[] = L"ZetCode";
	size_t target_size = 0;
	size_t size = sizeof(str);
	HRESULT r = StringCbLengthW(str, size, &target_size);
	if (SUCCEEDED(r)) {
		wprintf(L"The string has %d bytes\n", target_size);
	}
	else {
		wprintf(L"StringCbLengthW() failed\n");
		return 1;
	}
	size = sizeof(str) / sizeof(wchar_t);
	r = StringCchLengthW(str, size, &target_size);
	if (SUCCEEDED(r)) {
		wprintf(L"The string has %d characters\n", target_size);
	}
	else {
		wprintf(L"StringCchLengthW() failed\n");
		return 1;
	}

	return 0;
}

int safeGets()
{
	wchar_t buf[BUF_LEN2] = { 0 };
	HRESULT r = StringCchGetsW(buf, ARRAYSIZE(buf));
	if (SUCCEEDED(r)) {
		wprintf(L"You have entered: %ls\n", buf);
	}
	else {
		wprintf(L"StringCchGets() failed\n");
		return 1;
	}

	return 0;
}

int safeCopy()
{
	wchar_t* sentence = L"Today is a rainy day.";
	size_t size = wcslen(sentence) + 1;
	wchar_t buf[100];
	ZeroMemory(buf, size);
	HRESULT r = StringCchCopyW(buf, size, sentence);
	if (SUCCEEDED(r)) {
		wprintf(L"%ls\n", buf);
	}
	else {
		wprintf(L"StringCchCopyW() failed\n");
		return 1;
	}

	return 0;
}

int safeConcat()
{
	wchar_t buf[BUF_LEN3] = { 0 };
	HRESULT r = StringCchCatW(buf, BUF_LEN3, L"Hello ");
	if (FAILED(r)) {
		wprintf(L"StringCchCatW() failed\n");
		return 1;
	}
	r = StringCchCatW(buf, BUF_LEN3, L"there");
	if (FAILED(r)) {
		wprintf(L"StringCchCatW() failed\n");
		return 1;
	}
	wprintf(L"%ls\n", buf);

	return 0;
}

int safeFormat()
{
	wchar_t* word = L"table";
	int count = 6;
	wchar_t buf[BUF_LEN3] = { 0 };
	wchar_t* line = L"There are %d %lss";
	HRESULT r = StringCchPrintfW(buf, ARRAYSIZE(buf), line,
		count, word);
	if (SUCCEEDED(r)) {
		wprintf(L"%ls\n", buf);
	}
	else {
		wprintf(L"StringCchPrintfW() failed\n");
		return 1;
	}

	return 0;
}


