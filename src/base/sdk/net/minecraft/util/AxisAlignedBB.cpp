#include "AxisAlignedBB.h"

#include "../../../../java/java.h"
#include "../../../../util/logger.h"
#include "../../../strayCache.h"

//CAxisAlignedBB::CAxisAlignedBB()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::axisAlignedBB_class;
//}
//
//CAxisAlignedBB::CAxisAlignedBB(jobject instance) : CAxisAlignedBB()
//{
//	this->Instance = instance;
//}
//
//jclass CAxisAlignedBB::getClass()
//{
//	return this->Class;
//}
//
//jobject CAxisAlignedBB::getInstance()
//{
//	return this->Instance;
//}

BoundingBox CAxisAlignedBB::GetNativeBoundingBox(JNIEnv* env )
{
	return BoundingBox{
		env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minX),
		env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minY),
		env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minZ),

		env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxX),
		env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxY),
		env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxZ),
	};
}

void CAxisAlignedBB::SetBoundingBox(BoundingBox newBoundingBox, JNIEnv* env )
{
	env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minX, newBoundingBox.minX);
	env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minY, newBoundingBox.minY);
	env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minZ, newBoundingBox.minZ);

	env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxX, newBoundingBox.maxX);
	env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxY, newBoundingBox.maxY);
	env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxZ, newBoundingBox.maxZ);
}
