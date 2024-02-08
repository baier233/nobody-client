#pragma once
#include <Windows.h>
//https://www.youtube.com/watch?v=jTl3MFVKSUM
class Hook {
public:
	static bool hook(void* toHook, void* ourFunc, int len) {
		if (len < 5)
			return false;
		DWORD currprot;
		VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &currprot);

		memset(toHook, 0x90, len);

		DWORD relativeAddr = ((DWORD)ourFunc - (DWORD)toHook) - 5;

		*(BYTE*)toHook = 0xe9;
		*(DWORD*)((DWORD)toHook + 1) = relativeAddr;

		DWORD temp;
		VirtualProtect(toHook, len, currprot, &temp);
		
		return true;
	}
};