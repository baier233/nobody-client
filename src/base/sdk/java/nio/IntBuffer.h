#pragma once
#include "../../Object.h"
class IntBuffer : public Object
{
public:
	using Object::Object;
	Matrix GetMatrix(JNIEnv* env = Java::Env);
};

