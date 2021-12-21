#include <iostream>
#include <tchar.h>
#include "ProcessScanner.h"

int main()
{
	//PS::GetProcessList();
	DWORD processID = 0x0000196C;
	const char* processName = "firefox.exe";

	if (PS::GetProcessByID(processID))
	{
		_tprintf(TEXT("\nFound process of ID 0x%08X"), processID);
	}
	if (PS::GetProcessByName(processName))
	{
		_tprintf(TEXT("\nFound process by name %s"), processName);
	}
}
