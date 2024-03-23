#include "main.h"
#include "base/util/logger.h"
#include <Psapi.h>

DWORD Main::Init(HANDLE _)
{
	Base::Init();
	return NULL;
}

void Main::Kill()
{
	Base::Kill();
	FreeLibraryAndExitThread(Main::HModule, 0);
}
#include "base/java/java.h"
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Main::HModule = hModule;
		DisableThreadLibraryCalls(hModule);

		HANDLE hThread = CreateThread(nullptr, 0, Main::Init, hModule, 0, nullptr);
		
		if (hThread) CloseHandle(hThread);
	}

	if (dwReason == DLL_PROCESS_DETACH)
	{
		Main::Kill();
	}

	return TRUE;
}