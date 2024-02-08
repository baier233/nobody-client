#include "../../../../ext/minhook/minhook.h"
#include "../menu.h"
#include "../../sdk/sdk.h"
#include "../../moduleManager/commonData.h"
typedef void(__cdecl* OnUpdate) (void**, void**);
OnUpdate originalOnUpdate;
OnUpdate patchedOnUpdate;
void OnUpdatePatch(void** p1, void** p2)
{
	CommonData::getInstance()->post = true;
	originalOnUpdate(p1, p2);
}

void Menu::HookUpdate()
{
	MH_STATUS status = MH_UNKNOWN;
	while (status != MH_OK)
	{
		if (JNIHelper::IsForge()) {
			CMinecraft* minecraftInstance = SDK::Minecraft;
			if (minecraftInstance->getClass() == NULL) return;

			jmethodID OnUpdateMethod = Java::Env->GetMethodID(minecraftInstance->getClass(), "func_175161_p", "()V"); // maybe i should use func_71411_J instead?
			if (OnUpdateMethod == NULL) return;

			patchedOnUpdate = OnUpdate(*(unsigned __int64*)(*(unsigned __int64*)OnUpdateMethod + 0x40));

			status = MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));
			if (status != MH_OK) Sleep(50);
			else return;
		}
		CMinecraft* minecraftInstance = SDK::Minecraft;
		if (minecraftInstance->getClass() == NULL) return;

		jmethodID OnUpdateMethod = Java::Env->GetMethodID(minecraftInstance->getClass(), "onUpdateWalkingPlayer", "()V"); // maybe i should use func_71411_J instead?
		if (OnUpdateMethod == NULL) return;

		patchedOnUpdate = OnUpdate(*(unsigned __int64*)(*(unsigned __int64*)OnUpdateMethod + 0x40));

		status = MH_CreateHook(patchedOnUpdate, &OnUpdatePatch, (void**)(&originalOnUpdate));
		if (status != MH_OK) Sleep(50);
	}
}

void Menu::UnhookUpdate() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
}