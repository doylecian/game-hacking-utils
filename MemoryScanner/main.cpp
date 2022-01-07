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
	int onGroundOffsets[2] = { 0x778, 0x1634 };

	if (gameHandle)
	{
		_tprintf(TEXT("\nFound game handle"));
		_tprintf(TEXT("\nFound process ID of game: %d"), processID);
		_tprintf(TEXT("\nFound game base address: 0x%X"), gameBaseAddress);
		_tprintf(TEXT("\nFound client module base address: 0x%X"), clientBaseAddress);
		
		ReadProcessMemory(gameHandle, (PBYTE*)(clientBaseAddress + clientOffset), &offsetClientAddress, sizeof(int), 0);
		_tprintf(TEXT("\nClient module + offset: 0x%X + 0x%X -> 0x%X"), clientBaseAddress, clientOffset, offsetClientAddress);

		ReadProcessMemory(gameHandle, (PBYTE*)(offsetClientAddress + onGroundOffsets[0]), &L1GroundAddress, sizeof(int), 0);
		_tprintf(TEXT("\nL1 offset: 0x%X + 0x%X -> 0x%X"), offsetClientAddress, onGroundOffsets[0], L1GroundAddress);

		while (true)
		{
			ReadProcessMemory(gameHandle, (PBYTE*)(L1GroundAddress + onGroundOffsets[1]), &onGroundFlag, sizeof(int), 0);
			if (onGroundFlag == 0)
			{
				keybd_event(VK_SPACE, 0x39, NULL, NULL);
				std::this_thread::sleep_for(std::chrono::milliseconds(15));
				keybd_event(VK_SPACE, 0x39, KEYEVENTF_KEYUP, NULL);
			}	
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}

	CloseHandle(gameHandle);

}
