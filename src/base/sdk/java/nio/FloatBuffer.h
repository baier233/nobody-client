#pragma once

#include "../../Object.h"
#include "../../../util/math/geometry.h"

class FloatBuffer : public Object
{
public:
	using Object::Object;
	Matrix GetMatrix(JNIEnv* env = Java::GetInstance()->Env);
};

