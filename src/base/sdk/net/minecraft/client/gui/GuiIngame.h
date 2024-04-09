#pragma once
#include "../../../../Object.h"
#include "../../../../java/lang/String.h"
#include "GuiPlayerTabOverlay.h"

class CGuiIngame : public Object {
public:
	using Object::Object;
	CGuiPlayerTabOverlay getTabList(JNIEnv* env = Java::GetInstance()->Env);

};