#pragma once
#include <windows.h>

namespace PS
{
	HANDLE getProcessByName(char* processName);
	HANDLE getProcessByID(DWORD processID);
	BOOL GetProcessList();
}