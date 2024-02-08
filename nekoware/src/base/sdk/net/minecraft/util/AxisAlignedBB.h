#pragma once

#include "../../../Object.h"
#include "../../../../util/math/geometry.h"
#include "../../../strayCache.h"

class CAxisAlignedBB : public Object
{
	//CAxisAlignedBB();
	//CAxisAlignedBB(jobject instance);

	//jclass getClass();
	//jobject getInstance();
public:
	using Object::Object;
	BoundingBox GetNativeBoundingBox(JNIEnv* env = Java::Env);
	void SetBoundingBox(BoundingBox newBoundingBox, JNIEnv* env = Java::Env);
};

