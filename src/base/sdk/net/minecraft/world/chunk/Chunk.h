#pragma once
#include "../../block/Block.h"
#include "../../../../Object.h"
#include "../../entity/player/EntityPlayer.h"
#include "../../../../../util/math/geometry.h"

#include <vector>

class CChunk : public Object
{
	//CChunk(jobject);

	//jclass getClass() { return this->Class; };
	//jobject getInstance() {return this->Instance;};
	//
public:
	using Object::Object;
	CBlock getBlock(jint x, jint y, jint z, JNIEnv* env = Java::GetInstance()->Env);
};

