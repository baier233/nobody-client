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

BoundingBox CAxisAlignedBB::GetNativeBoundingBox()
{
	return BoundingBox{
		Java::Env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minX),
		Java::Env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minY),
		Java::Env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minZ),

		Java::Env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxX),
		Java::Env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxY),
		Java::Env->GetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxZ),
	};
}

void CAxisAlignedBB::SetBoundingBox(BoundingBox newBoundingBox)
{
	Java::Env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minX, newBoundingBox.minX);
	Java::Env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minY, newBoundingBox.minY);
	Java::Env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_minZ, newBoundingBox.minZ);

	Java::Env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxX, newBoundingBox.maxX);
	Java::Env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxY, newBoundingBox.maxY);
	Java::Env->SetDoubleField(this->getInstance(), StrayCache::axisAlignedBB_maxZ, newBoundingBox.maxZ);
}
