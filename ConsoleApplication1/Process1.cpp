
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

int main()
{
	srand(time(NULL));
	int n;
	cout << "Enter size\n";
	cin >> n;
	int* a = new int[n];

	wstring CommandLine = L"Process2.exe";
	wstring temp;

	for (int i = 0; i < n; i++)
	{
		CommandLine.append(L" ");
		temp = to_wstring(rand() % 10);
		CommandLine.append(temp);
	}
	wchar_t* arg = new wchar_t[CommandLine.length() + 1];
	wcscpy(arg, CommandLine.c_str());

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	si.lpTitle = (LPWSTR)L"QWERTY";
	si.dwFillAttribute = FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	si.dwFlags = STARTF_USEFILLATTRIBUTE | STARTF_USEPOSITION;
	si.dwX = (DWORD)400;

	CreateProcess(NULL, (LPWSTR) arg, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	WaitForSingleObject(pi.hProcess, INFINITE);
}