#include "ProcessUtils.h"

// Returns a handle to the process with the given name
HANDLE process::GetProcessByName(const char* processName)
{
	HANDLE hProcessSnap;
	HANDLE targetProcess;
	PROCESSENTRY32 processEntry;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	if (hProcessSnap == INVALID_HANDLE_VALUE || !Process32First(hProcessSnap, &processEntry))
	{
		_tprintf(TEXT("\nError occured trying to find process list"));
		CloseHandle(hProcessSnap);
		return(NULL);
	}

	do
	{
		if (!strcmp(processName, processEntry.szExeFile))
		{
			CloseHandle(hProcessSnap);
			targetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry.th32ProcessID);
			return(targetProcess);
		}
	} while (Process32Next(hProcessSnap, &processEntry));
	return NULL;
}

// Returns a handle to the process with the given ID
HANDLE process::GetProcessByID(DWORD processID)
{
	HANDLE hProcessSnap;
	HANDLE targetProcess;
	PROCESSENTRY32 processEntry;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	if (hProcessSnap == INVALID_HANDLE_VALUE || !Process32First(hProcessSnap, &processEntry))
	{
		_tprintf(TEXT("\nError occured trying to find process list"));
		CloseHandle(hProcessSnap);
		return(NULL);
	}

	do
	{
		if (processID == processEntry.th32ProcessID)
		{
			CloseHandle(hProcessSnap);
			targetProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry.th32ProcessID);
			return(targetProcess);
		}
	} while (Process32Next(hProcessSnap, &processEntry));
}

// Prints list of currently running processes
BOOL process::GetProcessList()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 processEntry;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE || !Process32First(hProcessSnap, &processEntry))
	{
		CloseHandle(hProcessSnap);
		return(FALSE);
	}
	else
	{
		processEntry.dwSize = sizeof(PROCESSENTRY32);
		do
		{
			_tprintf(TEXT("\nPROCESS NAME:  %s"), processEntry.szExeFile);
			_tprintf(TEXT("\n  Process ID        = 0x%08X"), processEntry.th32ProcessID);
		} while (Process32Next(hProcessSnap, &processEntry));

		CloseHandle(hProcessSnap);
		return(TRUE);
	}
}
