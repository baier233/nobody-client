#include "WSA.h"

#include "../menu.h"
#include "../../util/logger.h"
#include "../../../../ext/minhook/minhook.h"
#include "../../moduleManager/modules/player/blink.h"
#include "../../eventManager/EventManager.hpp"
#include "../../eventManager/events/EventPacketSend.h"

int(__stdcall* g_origWSASend)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
int __stdcall WSASendHook(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	//EventManager::getInstance().call(EventPacketSend((const char*)lpBuffers));
	while (Blink::getInstance()->getToggle()) {
		
		Sleep(1);
	}
	return g_origWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

int(__stdcall* g_origWSARecev)(SOCKET, LPWSABUF, DWORD, LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
int __stdcall WSARecevHook(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{

	while (Blink::getInstance()->getToggle()) {

		Sleep(1);
	}
	return g_origWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

void Menu::Hook_WSA() {

	MH_CreateHookApi(L"Ws2_32.dll", "WSASend", WSASendHook, (void**)&g_origWSASend);
	MH_EnableHook(MH_ALL_HOOKS);

}

void Menu::Unhook_WSA() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
} 