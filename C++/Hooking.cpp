#include "Hooking.h"


bool Hook::HookFunction(BYTE* targetFunction, BYTE* sourceFunction, int bytes)
{
	if (bytes < 5) return false;

	DWORD cProtection;

	VirtualProtect(targetFunction, bytes, PAGE_EXECUTE_READWRITE, &cProtection);

	*targetFunction = ASM_JMP; 
	*(uintptr_t*)(targetFunction + 1) = uintptr_t(sourceFunction - targetFunction - 5);

	VirtualProtect(targetFunction, bytes, cProtection, &cProtection);

	return true;
}

void Hook::UnHookFunction(BYTE* targetFunction, BYTE* originalFunction, int bytes) {
	DWORD cProtection;

	VirtualProtect(targetFunction, bytes, PAGE_EXECUTE_READWRITE, &cProtection);

	memcpy(targetFunction, originalFunction, bytes);

	VirtualProtect(targetFunction, bytes, cProtection, &cProtection);
}

uintptr_t Hook::FindPattern(uintptr_t moduleAddress, int moduleSize, HANDLE gameHandle, std::vector<int> signature)
{
	std::vector<BYTE> memBuffer(moduleSize);
	ReadProcessMemory(gameHandle, (LPCVOID)moduleAddress, memBuffer.data(), moduleSize, NULL);

	for (int i = 0; i < moduleSize; i++) {
		for (uintptr_t j = 0; j < signature.size(); j++) {
			if (signature.at(j) != -1 && signature[j] != memBuffer[i + j])
				//std::cout << std::hex << signature.at(j) << std::hex << memBuffer[i + j] << std::endl;
				break;
			if (signature[j] == memBuffer[i + j] && j > 0)
				//std::cout << std::hex << int(signature[j]) << std::hex << int(memBuffer[i + j]) << j << std::endl;
			if (j + 1 == signature.size())
				return moduleAddress + i;
		}
	}
	return 0xDEADBEEF;
}

