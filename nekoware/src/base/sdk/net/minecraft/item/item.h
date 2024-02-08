#pragma once
#include "../../../Object.h"

class CItem : public Object
{
public:
	using Object::Object;
	int GetIdFromItem(CItem item, JNIEnv* env = Java::Env);
};