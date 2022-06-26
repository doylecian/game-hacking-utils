#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>

namespace process
{
	HANDLE GetProcessByName(const char* processName);
	HANDLE GetProcessByID(DWORD processID);
	BOOL GetProcessList();
}