#pragma once
#include <windows.h>
#include <vector>
#include <iostream>

#define ASM_NOP 0x90
#define ASM_JMP 0xE9

namespace Hook
{
	bool HookFunction(BYTE* targetFunction, BYTE* sourceFunction, int bytes);
	void UnHookFunction(BYTE*  targetFunction, BYTE*  originalFunction, int bytes);
	uintptr_t FindPattern(uintptr_t moduleAddress, int moduleSize, HANDLE gameHandle, std::vector<int> signature);
}

