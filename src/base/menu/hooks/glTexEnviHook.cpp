#include "glTexEnviHook.h"

#include "../menu.h"
#include "../../../../ext/minhook/minhook.h"
#include "../../eventManager/EventManager.hpp"
#include <gl/GL.h>
#include "../../../../ext/jni/jni.h"
#include "../../eventManager/events/EventChams.hpp"
#include <iostream>

typedef __int64(__fastcall* Java_org_lwjgl_opengl_GL11_nglTexEnvi) (void** env, void** clazz ,GLenum target, GLenum pname, GLint param, void** functionpointer);

Java_org_lwjgl_opengl_GL11_nglTexEnvi original_glTexEnvi;

__int64 hknglTexEnvi(void** env, void** clazz, GLenum target, GLenum pname, GLint param, void** functionpointer) {
	EventChams event(target, pname, param);
	EventManager::getInstance().call(event);
	if (target == GL_TEXTURE_ENV)
	{
		std::cout << "onRender" << std::endl;
	}
	return original_glTexEnvi(env,clazz,target,pname, param,functionpointer);
}

//This is not work.



void Menu::Hook_glTexEnvi() {
	//MH_CreateHookApi(L"lwjgl64", "Java_org_lwjgl_opengl_GL11_nglTexEnvi", hknglTexEnvi, (LPVOID*)&original_glTexEnvi);
	//MH_EnableHook(MH_ALL_HOOKS);
}

void Menu::UnHook_glTexEnvi() {
	//MH_DisableHook(MH_ALL_HOOKS);
	//MH_RemoveHook(MH_ALL_HOOKS);
}