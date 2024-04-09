#pragma once

#include "../../../../../Object.h"
#include "../../../../../../util/math/geometry.h"

class CRenderManager :public Object
{
public:
	using Object::Object;
	Vector3 RenderPos(JNIEnv* env = Java::GetInstance()->Env);
	Vector3 ViewerPos(JNIEnv* env = Java::GetInstance()->Env);
	Vector2 PlayerView(JNIEnv* env = Java::GetInstance()->Env);
};

