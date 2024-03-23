#pragma once

#include "../../../../Object.h"
#include "../../../../../util/math/geometry.h"


class CActiveRenderInfo
{
public:
	static Matrix ProjectionMatrix(JNIEnv* env = Java::GetInstance()->Env);
	static Matrix ModelViewMatrix(JNIEnv* env = Java::GetInstance()->Env);
	static int Get_VIEWPORT(JNIEnv* env = Java::GetInstance()->Env);
};

