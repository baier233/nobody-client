#include "BlockPos.h"
#include "../../../../util/logger.h"
//BlockPos::BlockPos()
//{
//    if (!StrayCache::initialized) StrayCache::Initialize();
//    this->Class = StrayCache::axisAlignedBB_class;
//
//}
//
//BlockPos::BlockPos(jobject instance)
//{
//    this->Instance = instance;
//
//}
//
//jclass BlockPos::getClass()
//{
//    return this->Class;
//}
//
//jobject BlockPos::getInstance()
//{
//    return this->Instance;
//}

Vector3 BlockPos::getPos(JNIEnv* env)
{
	if (this->getInstance() == NULL) {
		return Vector3(NULL, NULL, NULL);
	}
	jint x{}, y{}, z{};
	x = env->GetIntField(this->instance, StrayCache::blockPos_x);
	y = env->GetIntField(this->getInstance(), StrayCache::blockPos_y);
	z = env->GetIntField(this->getInstance(), StrayCache::blockPos_z);
	return Vector3(x, y, z);
}

