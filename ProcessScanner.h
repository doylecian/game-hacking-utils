#pragma once
#include <windows.h>
#include <map>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

namespace PS
{
	HANDLE GetProcessByName(const char* processName);
	HANDLE GetProcessByID(DWORD processID);
	BOOL GetProcessList();
}