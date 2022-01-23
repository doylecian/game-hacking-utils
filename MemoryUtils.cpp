#include "MemoryUtils.h"

uintptr_t memory::GetBaseAddress(DWORD processID)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (modEntry.th32ProcessID == processID)
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t memory::GetBaseModuleAddress(DWORD processID, const wchar_t * moduleName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {

				// Convert to a wchar_t* 
				size_t origsize = strlen(modEntry.szModule) + 1;
				const size_t newsize = 100;
				size_t convertedChars = 0;
				wchar_t wchar_szModule[newsize];
				mbstowcs_s(&convertedChars, wchar_szModule, origsize, modEntry.szModule, _TRUNCATE);
				//_tprintf(TEXT("\nModule name:  %s"), modEntry.szModule); 
				if (!_wcsicmp(wchar_szModule, moduleName)) {
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t memory::ResolvePointerChain(HANDLE processHandle, uintptr_t baseAddress, std::vector<int> offsets)
{
	uintptr_t tempAddress = baseAddress;
	for (int i = 0; i < offsets.size(); i++)
	{
		ReadProcessMemory(processHandle, (PBYTE*)(tempAddress + offsets[i]), &tempAddress, sizeof(tempAddress), 0);
	}
	return tempAddress;
}