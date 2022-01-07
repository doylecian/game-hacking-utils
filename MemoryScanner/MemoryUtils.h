#pragma once
#include "MemoryUtils.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>

namespace memory
{
	uintptr_t GetBaseAddress(DWORD processID);
	uintptr_t GetBaseModuleAddress(DWORD processID, const wchar_t * moduleName);
	uintptr_t ResolvePointerChain(HANDLE processHandle, uintptr_t baseAddress, std::vector<int>);
}
