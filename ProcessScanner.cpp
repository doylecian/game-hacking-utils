#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include "ProcessScanner.h"

// Returns a handle to the process with the given name
HANDLE PS::getProcessByName(char* processName)
{
	//TODO: IMPLEMENT THIS
	return NULL;
}
// Returns a handle to the process with the given ID
HANDLE PS::getProcessByID(DWORD processID)
{
	//TODO: IMPLEMENT THIS
	return NULL;
}

// Prints all the currently running processes to the terminal
BOOL PS::GetProcessList()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 processEntry;

	// Take a snapshot of all processes
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap != INVALID_HANDLE_VALUE && Process32First(hProcessSnap, &processEntry))
	{
		// Set the size of the structure before using it.
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		// Iterate through processes and print them to terminal
		do
		{
			_tprintf(TEXT("\nPROCESS NAME:  %s"), processEntry.szExeFile);
			_tprintf(TEXT("\n  Process ID        = 0x%08X"), processEntry.th32ProcessID);
		} while (Process32Next(hProcessSnap, &processEntry));

		CloseHandle(hProcessSnap);
		return(TRUE);
	}
}
