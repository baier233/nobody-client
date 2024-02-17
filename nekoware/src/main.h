#pragma once

#include <Windows.h>
#include "base/base.h"

class Main
{
public:
	static DWORD Init(HANDLE _);
	static void Kill();

	static inline HMODULE HModule;
};

