#include <iostream>
#include <tchar.h>
#include "ProcessUtils.h"
#include "MemoryUtils.h"



int main()
{

	HANDLE gameHandle = process::GetProcessByName("left4dead.exe");
	DWORD processID = GetProcessId(gameHandle);
	uintptr_t gameBaseAddress = memory::GetBaseAddress(processID);
	uintptr_t clientBaseAddress = memory::GetBaseModuleAddress(processID, L"client.dll");

	if (gameHandle)
	{
		_tprintf(TEXT("\nFound game handle"));
		_tprintf(TEXT("\nFound process ID of game: %d [0x%X]"), processID, processID);
		_tprintf(TEXT("\nFound game base address: %d [0x%X]"), gameBaseAddress, gameBaseAddress);
		_tprintf(TEXT("\nFound client module base address: %d [0x%X]"), clientBaseAddress, clientBaseAddress);
	}

	int close;
	std::cin >> close;

	CloseHandle(gameHandle);

}
