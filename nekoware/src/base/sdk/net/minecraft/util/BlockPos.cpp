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

Vector3 BlockPos::getPos(JNIEnv* env )
{
	if (this->getInstance() == NULL) {
		return Vector3(NULL, NULL, NULL);
	}
	Logger::Log("getPos");
	jint x = env->GetIntField(this->getInstance(), StrayCache::blockPos_x);
	jint y = env->GetIntField(this->getInstance(), StrayCache::blockPos_y);
	jint z = env->GetIntField(this->getInstance(), StrayCache::blockPos_z);
	return Vector3(x, y, z);
}

