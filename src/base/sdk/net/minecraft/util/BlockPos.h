#pragma once

#include "../../../Object.h"
#include "../../../../util/math/geometry.h"
#include "../../../strayCache.h"

class BlockPos :public Object
{
	//BlockPos();
	//BlockPos(jobject instance);

	//jclass getClass();
	//jobject getInstance();
public:
	using Object::Object;
	Vector3 getPos(JNIEnv* env = Java::Env);
};