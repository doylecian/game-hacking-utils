#include <iostream>
#include <tchar.h>
#include <chrono>
#include <thread>
#include "ProcessUtils.h"
#include "MemoryUtils.h"

int main()
{

	HANDLE gameHandle = process::GetProcessByName("left4dead.exe");
	uintptr_t processID = GetProcessId(gameHandle);
	uintptr_t gameBaseAddress = memory::GetBaseAddress(processID);
	uintptr_t clientBaseAddress = memory::GetBaseModuleAddress(processID, L"client.dll");
	uintptr_t offsetClientAddress;					                                 
	uintptr_t L1GroundAddress;
	int onGroundFlag;
	int clientOffset = 0x517200;
	std::vector<int> onGroundOffsets = { 0x778, 0x1634 };

	if (gameHandle)
	{
		_tprintf(TEXT("\nFound game handle"));
		_tprintf(TEXT("\nFound process ID of game: %d"), processID);
		_tprintf(TEXT("\nFound game base address: 0x%X"), gameBaseAddress);
		_tprintf(TEXT("\nFound client module base address: 0x%X"), clientBaseAddress);
		
		ReadProcessMemory(gameHandle, (PBYTE*)(clientBaseAddress + clientOffset), &offsetClientAddress, sizeof(int), 0);
		_tprintf(TEXT("\nClient module + offset: 0x%X + 0x%X -> 0x%X"), clientBaseAddress, clientOffset, offsetClientAddress);

		while (true)
		{
			onGroundFlag = (int)memory::ResolvePointerChain(gameHandle, offsetClientAddress, onGroundOffsets);
			_tprintf(TEXT("\nJump flag %d"), onGroundFlag);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}	
	}

	CloseHandle(gameHandle);
}
