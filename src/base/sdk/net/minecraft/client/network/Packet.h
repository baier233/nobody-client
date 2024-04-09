#pragma once
#include "../../../../Object.h"
#include "../../../../java/lang/String.h"
class CPacket :public Object
{
public:
	using Object::Object;
	std::string ToString(JNIEnv* env = Java::GetInstance()->Env);
};
